/*
 * Dstroy, a remake of the bomberman-like DOS game from Fully Bugged Software
 * Copyright (C) Michael Doguet
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


#include "stdafx.h"
#include "TGIGlobals.h"

#include <iostream>
#include <string>

#include "TGIMain.h"

#include <vitasdk.h>
#include <vitaGL.h>
#include <imgui_vita.h>

int _newlib_heap_size_user = 192 * 1024 * 1024;

TGIMain* TGIGlobals::theMain = NULL;
SDL_Surface* TGIGlobals::pScreen = NULL;
TGIint TGIGlobals::screenWidth = 0;
TGIint TGIGlobals::screenHeight = 0;
bool TGIGlobals::bRotateScreen = false;
#ifndef TGI_NOSOUND
#ifndef __NDS__
Mix_Music* TGIGlobals::pMusic = NULL;
TGIuint16 TGIGlobals::nRepeat = 0;
TGIuint16 TGIGlobals::nRepeatPos = 0;
#else
int TGIGlobals::nMusicRes = -1;
#endif //__NDS__
#endif
std::vector<SDL_Joystick*> TGIGlobals::vecJoystick;
TGIuint8 TGIGlobals::nSpriteSize = 1;
#ifdef GP2X
TGIuint8 TGIGlobals::nGP2XmvtMode = 1;
#endif

TGIGlobals::TGIGlobals(void)
{
}

TGIGlobals::~TGIGlobals(void)
{
}

#ifdef _TGI_DEBUG
void LOG2FILE(const char *format, ...) {
	__gnuc_va_list arg;
	int done;
	va_start(arg, format);
	char msg[512];
	done = vsprintf(msg, format, arg);
	va_end(arg);
	int i;
	sprintf(msg, "%s\n", msg);
	FILE* log = fopen("ux0:/data/dstroy.log", "a+");
	if (log != NULL) {
		fwrite(msg, 1, strlen(msg), log);
		fclose(log);
	}
}
#endif

void TGIGlobals::Trace(std::string strMessage, ...)
{
	//a refaire
#ifdef _TGI_DEBUG
	LOG2FILE("%s",strMessage.c_str());
#endif

}

bool credits = false;
bool bilinear = true;
bool vflux_window = false;
bool res_window = false;
bool credits_window = false;
bool vflux_enabled = false;
bool hide_menubar = false;
bool show_menubar = true;
bool vsync = true;
float vcolors[3];
uint16_t *vindices;
float *colors;
float *vflux_vertices;
float *vflux_texcoords;

int screen_x = 0;
int screen_y = 0;
float screen_res_w = 960.0f;
float screen_res_h = 544.0f;
float old_screen_res_w = 960.0f;
float old_screen_res_h = 544.0f;

uint64_t tmr1;
SDL_Shader shader = SDL_SHADER_NONE;
bool cfg_exists = false;

// PostFX effects
enum {
	POSTFX_NONE,
	POSTFX_FXAA,
	POSTFX_GREYSCALE,
	POSTFX_SEPIA,
	POSTFX_NEGATIVE
};
uint32_t postfx_shader = 0;
GLuint main_fb = 0xDEADBEEF, main_fb_tex;
GLuint cur_fx_shader[2] = {0xDEADBEEF, 0xDEADBEEF};
static GLuint fx_fs[2], fx_vs[2];
int postfx_idx = 0;

void GL_LoadFXShader(const char* filename, GLboolean fragment){
	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	void* res = malloc(size);
	fread(res, 1, size, f);
	fclose(f);
	if (fragment) glShaderBinary(1, &fx_fs[postfx_idx], 0, res, size);
	else glShaderBinary(1, &fx_vs[postfx_idx], 0, res, size);
	free(res);
}

void setupPostFxFb() {
	if (main_fb == 0xDEADBEEF) {
		glGenTextures(1, &main_fb_tex);
		glBindTexture(GL_TEXTURE_2D, main_fb_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 960, 544, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glGenFramebuffers(1, &main_fb);
		glBindFramebuffer(GL_FRAMEBUFFER, main_fb);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, main_fb_tex, 0);
	}
	SDL_SetVideoFrameBuffer(main_fb);
}

void loadPostFxEffect(const char *vertex, const char *fragment)
{
	postfx_idx = (postfx_idx + 1) % 2;
	if (cur_fx_shader[postfx_idx] != 0xDEADBEEF) {
		glDeleteProgram(cur_fx_shader[postfx_idx]);
		glDeleteShader(fx_vs[postfx_idx]);
		glDeleteShader(fx_fs[postfx_idx]);
	}
	fx_vs[postfx_idx] = glCreateShader(GL_VERTEX_SHADER);
	fx_fs[postfx_idx] = glCreateShader(GL_FRAGMENT_SHADER);
	cur_fx_shader[postfx_idx] = glCreateProgram();
	GL_LoadFXShader(vertex, GL_FALSE);
	GL_LoadFXShader(fragment, GL_TRUE);
	glAttachShader(cur_fx_shader[postfx_idx], fx_vs[postfx_idx]);
	glAttachShader(cur_fx_shader[postfx_idx], fx_fs[postfx_idx]);
	vglBindAttribLocation(cur_fx_shader[postfx_idx], 0, "position", 3, GL_FLOAT);
	vglBindAttribLocation(cur_fx_shader[postfx_idx], 1, "texcoord", 2, GL_FLOAT);
	glLinkProgram(cur_fx_shader[postfx_idx]);
}

void loadImGuiCfg(){
	FILE *f = fopen("ux0:data/dstroydata/imgui.cfg", "rb");
	if (f){
		char str[256];
		fread(str, 1, 256, f);
		fclose(f);
		uint32_t a,b,c,d;
		sscanf(str, "%u;%u;%f;%f;%u;%u;%f;%f;%f;%u;%u", &a, &shader, &screen_res_w, &screen_res_h, &b, &c, &vcolors[0], &vcolors[1], &vcolors[2], &postfx_shader, &d);
		bilinear = (a == 1);
		hide_menubar = (b == 1);
		vflux_enabled = (c == 1);
		vsync = (d == 1);
		SDL_SetVideoShader(shader);
		SDL_SetVideoModeBilinear(bilinear);
		screen_x = (int)(960.0f - screen_res_w) / 2;
		screen_y = (int)(544.0f - screen_res_h) / 2;
		SDL_SetVideoModeScaling(screen_x, screen_y, screen_res_w, screen_res_h);
		SDL_SetVideoModeSync(vsync);
		cfg_exists = true;
	}
	if (postfx_shader != POSTFX_NONE) {
		setupPostFxFb();
		switch (postfx_shader) {
		case POSTFX_FXAA:
			loadPostFxEffect("app0:shaders/fxaa_v.gxp", "app0:shaders/fxaa_f.gxp");
			break;
		case POSTFX_GREYSCALE:
			loadPostFxEffect("app0:shaders/greyscale_v.gxp", "app0:shaders/greyscale_f.gxp");
			break;
		case POSTFX_SEPIA:
			loadPostFxEffect("app0:shaders/sepia_v.gxp", "app0:shaders/sepia_f.gxp");
			break;
		case POSTFX_NEGATIVE:
			loadPostFxEffect("app0:shaders/negative_v.gxp", "app0:shaders/negative_f.gxp");
			break;
		default:
			break;
		}
	}
}

void DoPostFX() {
	if (postfx_shader != 0) {
		vglStopRendering();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		vglStartRendering();
		glBindTexture(GL_TEXTURE_2D, main_fb_tex);
		glUseProgram(cur_fx_shader[postfx_idx]);
		vglIndexPointerMapped(vindices);
		vglVertexAttribPointerMapped(0, vflux_vertices);
		vglVertexAttribPointerMapped(1, vflux_texcoords);
		vglDrawObjects(GL_TRIANGLE_FAN, 4, true);
		glUseProgram(0);
	}
}

void ImGui_callback() {
	DoPostFX();
	
	ImGui_ImplVitaGL_NewFrame();
	
	if (show_menubar) {
		if (ImGui::BeginMainMenuBar()){
		
			if (ImGui::BeginMenu("Graphics")){
				if (ImGui::MenuItem("V-Sync", nullptr, vsync)){
					vsync = !vsync;
					SDL_SetVideoModeSync(vsync);
				}
				if (ImGui::MenuItem("Bilinear Filter", nullptr, bilinear)){
					bilinear = !bilinear;
					SDL_SetVideoModeBilinear(bilinear);
				}
				if (ImGui::MenuItem("vFlux Config", nullptr, vflux_window)){
					vflux_window = !vflux_window;
				}
				if (ImGui::MenuItem("Resolution", nullptr, res_window)){
					res_window = !res_window;
				}
				if (ImGui::BeginMenu("Shaders")){
					if (ImGui::MenuItem("None", nullptr, shader == SDL_SHADER_NONE)){
						shader = SDL_SHADER_NONE;
						SDL_SetVideoShader(SDL_SHADER_NONE);
					}
					if (ImGui::MenuItem("Sharp Bilinear", nullptr, shader == SDL_SHADER_SHARP_BILINEAR_SIMPLE)){
						shader = SDL_SHADER_SHARP_BILINEAR_SIMPLE;
						SDL_SetVideoShader(SDL_SHADER_SHARP_BILINEAR_SIMPLE);
					}
					if (ImGui::MenuItem("Sharp Bilinear (Scanlines)", nullptr, shader == SDL_SHADER_SHARP_BILINEAR)){
						shader = SDL_SHADER_SHARP_BILINEAR;
						SDL_SetVideoShader(SDL_SHADER_SHARP_BILINEAR);
					}
					if (ImGui::MenuItem("LCD 3x", nullptr, shader == SDL_SHADER_LCD3X)){
						shader = SDL_SHADER_LCD3X;
						SDL_SetVideoShader(SDL_SHADER_LCD3X);
					}
					if (ImGui::MenuItem("xBR x2", nullptr, shader == SDL_SHADER_XBR_2X_FAST)){
						shader = SDL_SHADER_XBR_2X_FAST;
						SDL_SetVideoShader(SDL_SHADER_XBR_2X_FAST);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Post Processing")){
					if (ImGui::MenuItem("None", nullptr, postfx_shader == POSTFX_NONE)){
						postfx_shader = POSTFX_NONE;
						SDL_SetVideoFrameBuffer(0);
					}
					if (ImGui::MenuItem("FXAA", nullptr, postfx_shader == POSTFX_FXAA)){
						postfx_shader = POSTFX_FXAA;
						loadPostFxEffect("app0:shaders/fxaa_v.gxp", "app0:shaders/fxaa_f.gxp");
						setupPostFxFb();
					}
					if (ImGui::MenuItem("Greyscale", nullptr, postfx_shader == POSTFX_GREYSCALE)){
						postfx_shader = POSTFX_GREYSCALE;
						loadPostFxEffect("app0:shaders/greyscale_v.gxp", "app0:shaders/greyscale_f.gxp");
						setupPostFxFb();
					}
					if (ImGui::MenuItem("Sepia Tone", nullptr, postfx_shader == POSTFX_SEPIA)){
						postfx_shader = POSTFX_SEPIA;
						loadPostFxEffect("app0:shaders/sepia_v.gxp", "app0:shaders/sepia_f.gxp");
						setupPostFxFb();
					}
					if (ImGui::MenuItem("Negative", nullptr, postfx_shader == POSTFX_NEGATIVE)){
						postfx_shader = POSTFX_NEGATIVE;
						loadPostFxEffect("app0:shaders/negative_v.gxp", "app0:shaders/negative_f.gxp");
						setupPostFxFb();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
		
			if (ImGui::BeginMenu("Extra")){
				if (ImGui::MenuItem("Hide Menubar", nullptr, hide_menubar)){
					hide_menubar = !hide_menubar;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Save settings")){
					FILE *f = fopen("ux0:data/dstroydata/imgui.cfg", "wb+");
					char str[256];
					sprintf(str, "%u;%u;%f;%f;%u;%u;%f;%f;%f;%u;%u", bilinear ? 1 : 0, shader, screen_res_w, screen_res_h, hide_menubar ? 1 : 0, vflux_enabled ? 1 : 0, vcolors[0], vcolors[1], vcolors[2], postfx_shader, vsync ? 1 : 0);
					fwrite(str, 1, strlen(str), f);
					fclose(f);
					cfg_exists = true;
				}
				if (ImGui::MenuItem("Load settings", nullptr, false, cfg_exists)){
					loadImGuiCfg();
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Credits", nullptr, credits_window)){
					credits_window = !credits_window;
				}
				ImGui::EndMenu();
			}
		
			ImGui::SameLine();
			ImGui::SetCursorPosX(870);
		
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate); 
			ImGui::EndMainMenuBar();
		}
	}
	
	if (vflux_window){
		ImGui::Begin("vFlux Configuration", &vflux_window);
		ImGui::ColorPicker3("Filter Color", vcolors);
		ImGui::Checkbox("Enable vFlux", &vflux_enabled);
		ImGui::End();
	}

	if (res_window){
		ImGui::Begin("Resolution", &res_window);
		ImGui::SliderFloat("Width", &screen_res_w, 0.0f, 960.0f, "%g");
		ImGui::SliderFloat("Height", &screen_res_h, 0.0f, 544.0f, "%g");
		if (ImGui::Button("Fit (4:3)")){
			screen_res_h = 544.0f;
			screen_res_w = (4.0f * screen_res_h) / 3.0f;
		}
		if (ImGui::Button("Fit (16:10)")){
			screen_res_h = 544.0f;
			screen_res_w = (16.0f * screen_res_h) / 10.0f;
		}
		if (ImGui::Button("Full")){
			screen_res_h = 544.0f;
			screen_res_w = 960.0f;
		}
		if (ImGui::Button("2x")){
			screen_res_h = 480.0f;
			screen_res_w = 640.0f;
		}
		ImGui::End();
	}

	if (credits_window){
		ImGui::Begin("Credits", &credits_window);
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "Dstroy Vita v.1.1");
		ImGui::Text("Port Author: Rinnegatamante");
		ImGui::Text("Tester: HtheB");
		ImGui::Separator();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "Patreon Supporters:");
		ImGui::Text("XandridFire");
		ImGui::Text("Freddy Parra");
		ImGui::Text("Tain Sueiras");
		ImGui::Text("Badmanwazzy37");
		ImGui::Text("Titi Clash");
		ImGui::Text("psymu");
		ImGui::Text("@Sarkies_Proxy");
		ImGui::Text("drd7of14");
		ImGui::Text("ArkSource");
		ImGui::Text("The Vita3K project");
		ImGui::Text("The Libretro Team");
		ImGui::Separator();
		ImGui::TextColored(ImVec4(255, 255, 0, 255), "Special thanks to:");
		ImGui::Text("rsn8887 for fixing shaders for vitaGL usage and multiple players support");
		ImGui::Text("ocornut for dear ImGui");
		ImGui::Text("HtheB for the Livearea assets");
		ImGui::Text("xy2_ for the English translation");
		ImGui::End();
	}
		
	ImGui::Render();
	ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
	
	if (vflux_enabled) {
		memcpy(&colors[0], vcolors, sizeof(float) * 3);
		memcpy(&colors[4], vcolors, sizeof(float) * 3);
		memcpy(&colors[8], vcolors, sizeof(float) * 3);
		memcpy(&colors[12], vcolors, sizeof(float) * 3);
		
		float a;
		SceDateTime time;
		sceRtcGetCurrentClockLocalTime(&time);
		if (time.hour < 6)		// Night/Early Morning
			a = 0.25f;
		else if (time.hour < 10) // Morning/Early Day
			a = 0.1f;
		else if (time.hour < 15) // Mid day
			a = 0.05f;
		else if (time.hour < 19) // Late day
			a = 0.15f;
		else // Evening/Night
			a = 0.2f;
		colors[3] = colors[7] = colors[11] = colors[15] = a;
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glUseProgram(0);
		vglIndexPointerMapped(vindices);
		vglVertexPointerMapped(vflux_vertices);
		vglColorPointerMapped(GL_FLOAT, colors);
		vglDrawObjects(GL_TRIANGLE_FAN, 4, true);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
	if ((old_screen_res_w != screen_res_w) || (old_screen_res_h != screen_res_h)) {
		screen_x = (int)(960.0f - screen_res_w) / 2;
		screen_y = (int)(544.0f - screen_res_h) / 2;
		SDL_SetVideoModeScaling(screen_x, screen_y, screen_res_w, screen_res_h);
	}
	old_screen_res_w = screen_res_w;
	old_screen_res_h = screen_res_h;
	
	SceTouchData touch;
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
	uint64_t delta_touch = sceKernelGetProcessTimeWide() - tmr1;
	if (touch.reportNum > 0){
		ImGui::GetIO().MouseDrawCursor = true;
		show_menubar = true;
		tmr1 = sceKernelGetProcessTimeWide();
	}else if (delta_touch > 3000000){
		ImGui::GetIO().MouseDrawCursor = false;
		show_menubar = !hide_menubar;
	}
}

bool TGIGlobals::init(TGIint screenWidth, TGIint screenHeight, TGIuint8 nSpriteSize, bool bFullScreen, bool bRotateScreen)
{
 	TGIGlobals::nSpriteSize = nSpriteSize;
	TGIGlobals::bRotateScreen = bRotateScreen;

	TGIGlobals::screenWidth = screenWidth;
	TGIGlobals::screenHeight = screenHeight;



	//SDL init
	TGIint err  = 0;
#ifndef __NDS__
	err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
#endif

	if (err < 0)
	{ 
		TGIGlobals::Trace("Cant initiate SDL: %s\n", SDL_GetError()); 
		return false;
	}
	TGIGlobals::Trace("SDL initiated");

	TGIGlobals::nSpriteSize = 2;
	TGIGlobals::screenWidth = 320;
	TGIGlobals::screenHeight = 240;

	scePowerSetArmClockFrequency(444);
	scePowerSetBusClockFrequency(222);
	scePowerSetGpuClockFrequency(222);
	scePowerSetGpuXbarClockFrequency(166);
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
	
	TGIGlobals::pScreen = SDL_SetVideoMode(TGIGlobals::screenWidth*nSpriteSize, TGIGlobals::screenHeight*nSpriteSize, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (pScreen == NULL)
	{
		TGIGlobals::Trace("Error while initializing screen\n");
		return false;
	}
	SDL_SetVideoModeScaling(0, 0, 960, 544);
	
	vindices = (uint16_t*)malloc(sizeof(uint16_t)*4);
	colors = (float*)malloc(sizeof(float)*4*4);
	vflux_vertices = (float*)malloc(sizeof(float)*3*4);
	vflux_texcoords = (float*)malloc(sizeof(float)*2*4);
	vflux_vertices[0] =   0.0f;
	vflux_vertices[1] =   0.0f;
	vflux_vertices[2] =   0.0f;
	vflux_vertices[3] = 960.0f;
	vflux_vertices[4] =   0.0f;
	vflux_vertices[5] =   0.0f;
	vflux_vertices[6] = 960.0f;
	vflux_vertices[7] = 544.0f;
	vflux_vertices[8] =   0.0f;
	vflux_vertices[9] =   0.0f;
	vflux_vertices[10]= 544.0f;
	vflux_vertices[11]=   0.0f;
	vflux_texcoords[0] = 0.0f;
	vflux_texcoords[1] = 0.0f;
	vflux_texcoords[2] = 1.0f;
	vflux_texcoords[3] = 0.0f;
	vflux_texcoords[4] = 1.0f;
	vflux_texcoords[5] = 1.0f;
	vflux_texcoords[6] = 0.0f;
	vflux_texcoords[7] = 1.0f;
	vindices[0] = 0;
	vindices[1] = 1;
	vindices[2] = 2;
	vindices[3] = 3;
	
	ImGui::CreateContext();
	ImGui_ImplVitaGL_Init();
	ImGui_ImplVitaGL_TouchUsage(true);
	ImGui_ImplVitaGL_MouseStickUsage(false);
	ImGui_ImplVitaGL_UseIndirectFrontTouch(true);
	ImGui::StyleColorsDark();
	ImGui::GetIO().MouseDrawCursor = false;
	
	SDL_SetVideoCallback(ImGui_callback);
	
	loadImGuiCfg();
	
	//joysticks
	int nJoys = SDL_NumJoysticks() - 1;
	SDL_Joystick* pJoy;
	for (;nJoys>=0;nJoys--)
	{
		pJoy = SDL_JoystickOpen(nJoys);
		if (pJoy)
		{
			vecJoystick.push_back(pJoy);
		}
	}
	//sound
#ifndef TGI_NOSOUND
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	int n;
	n = Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 128);
	Mix_HookMusicFinished(music_finished);
#endif

	SDL_ShowCursor(0);

	return true;
}

bool TGIGlobals::exit(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif
#endif

	
	for (TGIuint16 i=0;i<vecJoystick.size();i++)
	{
		SDL_JoystickClose(vecJoystick[i]);
	}

	SDL_Quit();

	return true;
}


void TGIGlobals::endianConvert(TGIuint16 order, void* pData, TGIuint16 nLen)
{
	if (order == 255)
	{
		//no need to convert
		return;
	}

	TGIint i;
	TGIuint8 t;
	for (i=nLen/2-1;i>=0;i--)
	{
		t = ((TGIuint8*)pData)[i];
		((TGIuint8*)pData)[i] = ((TGIuint8*)pData)[nLen-i-1];
		((TGIuint8*)pData)[nLen-i-1] = t;
	}
}


bool TGIGlobals::playMusic(std::string cstrFile, TGIuint16 nRepeat, TGIuint16 nRepeatPos)
{
#ifndef TGI_NOSOUND
	char strDebug[256];
	sprintf(strDebug, "playMusic:%s", cstrFile.c_str());
	TGIGlobals::Trace(strDebug);
	TGIGlobals::stopMusic();

#ifndef __NDS__
	TGIGlobals::pMusic = Mix_LoadMUS(cstrFile.c_str());
	if (!TGIGlobals::pMusic)
		return false;
	TGIGlobals::nRepeatPos = nRepeatPos;
	TGIGlobals::nRepeat = nRepeat - 1;

	return Mix_PlayMusic(TGIGlobals::pMusic, 1) == 0;
#else
	nMusicRes = file2res(cstrFile.c_str());
	sprintf(strDebug, "ressource=%d", nMusicRes);
	TGIGlobals::Trace(strDebug);
		
	mmLoad(nMusicRes);
	mmStart( nMusicRes, MM_PLAY_LOOP );
#endif

#endif
	return false;
}

bool TGIGlobals::stopMusic(void)
{
#ifndef TGI_NOSOUND
#ifndef __NDS__
	if (TGIGlobals::pMusic)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(TGIGlobals::pMusic);
		TGIGlobals::pMusic = NULL;
	}
#else
	//maxmod
	if (nMusicRes != -1)
	{
		if (mmActive())
		{
			mmStop( );
		}
		mmUnload(nMusicRes);

		nMusicRes = -1;
	}
#endif
#endif
	return true;
}
#ifndef TGI_NOSOUND
#ifndef __NDS__
void TGIGlobals::music_finished()
{

	if (nRepeat == 0)
		return;
	if (nRepeat > 0)
		nRepeat--;

	
	Mix_PlayMusic(TGIGlobals::pMusic, 1);
	Mix_PauseMusic();
	Mix_SetMusicPosition(nRepeatPos);
	Mix_ResumeMusic();

}
#endif
#endif
