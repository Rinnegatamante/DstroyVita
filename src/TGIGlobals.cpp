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
bool credits_window = false;
bool vflux_enabled = false;
float vcolors[3];
uint16_t *vindices;
float *colors;
float *vertices;
uint64_t tmr1;
SDL_Shader shader = SDL_SHADER_NONE;

void ImGui_callback() {
	
	ImGui_ImplVitaGL_NewFrame();
	
	if (ImGui::BeginMainMenuBar()){
		
		if (ImGui::BeginMenu("Graphics")){
			if (ImGui::MenuItem("Bilinear Filter", nullptr, bilinear)){
				bilinear = !bilinear;
				SDL_SetVideoModeBilinear(bilinear);
			}
			if (ImGui::MenuItem("vFlux Config", nullptr, vflux_window)){
				vflux_window = !vflux_window;
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
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Info")){
			if (ImGui::MenuItem("Credits", nullptr, credits_window)){
				credits_window = !credits_window;
			}
			ImGui::EndMenu();
		}
		
		
		if (vflux_window){
			ImGui::Begin("vFlux Configuration", &vflux_window);
			ImGui::ColorPicker3("Filter Color", vcolors);
			ImGui::Checkbox("Enable vFlux", &vflux_enabled);
			ImGui::End();
		}
		
		if (credits_window){
			ImGui::Begin("Credits", &credits_window);
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "Zelda: Oni Link Begins Vita v.1.5");
			ImGui::Text("Game Creator: Vincent Jouillat");
			ImGui::Text("Port Author: Rinnegatamante");
			ImGui::Text("Tester: ChrisHighwind");
			ImGui::Separator();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "Patreon Supporters:");
			ImGui::Text("XandridFire");
			ImGui::Text("Styde Pregny");
			ImGui::Text("Billy McLaughlin II");
			ImGui::Text("Colan Wiser");
			ImGui::Separator();
			ImGui::TextColored(ImVec4(255, 255, 0, 255), "Special thanks to:");
			ImGui::Text("rsn8887 for fixing shaders for vitaGL usage");
			ImGui::Text("ocornut for dear ImGui");
			ImGui::End();
		}
		
		ImGui::SameLine();
		ImGui::SetCursorPosX(870);
		
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate); 
		ImGui::EndMainMenuBar();
	}
	
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
		vglIndexPointerMapped(vindices);
		vglVertexPointerMapped(vertices);
		vglColorPointerMapped(GL_FLOAT, colors);
		vglDrawObjects(GL_TRIANGLE_FAN, 4, true);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
	ImGui::Render();
	ImGui_ImplVitaGL_RenderDrawData(ImGui::GetDrawData());
	
	SceTouchData touch;
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
	uint64_t delta_touch = sceKernelGetProcessTimeWide() - tmr1;
	if (touch.reportNum > 0){
		ImGui::GetIO().MouseDrawCursor = true;
		tmr1 = sceKernelGetProcessTimeWide();
	}else if (delta_touch > 3000000) ImGui::GetIO().MouseDrawCursor = false;
	
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
	//SDL_SetVideoModeScaling(0, 0, 960, 544);
	
	vindices = (uint16_t*)malloc(sizeof(uint16_t)*4);
	colors = (float*)malloc(sizeof(float)*4*4);
	vertices = (float*)malloc(sizeof(float)*3*4);
	vertices[0] =   0.0f;
	vertices[1] =   0.0f;
	vertices[2] =   0.0f;
	vertices[3] = 960.0f;
	vertices[4] =   0.0f;
	vertices[5] =   0.0f;
	vertices[6] = 960.0f;
	vertices[7] = 544.0f;
	vertices[8] =   0.0f;
	vertices[9] =   0.0f;
	vertices[10]= 544.0f;
	vertices[11]=   0.0f;
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
