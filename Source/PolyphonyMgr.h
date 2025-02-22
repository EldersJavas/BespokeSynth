/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  PolyphonyMgr.h
//  additiveSynth
//
//  Created by Ryan Challinor on 11/20/12.
//
//

#ifndef __additiveSynth__PolyphonyMgr__
#define __additiveSynth__PolyphonyMgr__

#include <iostream>
#include "OpenFrameworksPort.h"
#include "SynthGlobals.h"
#include "ChannelBuffer.h"

const int kVoiceFadeSamples = 50;

extern ChannelBuffer gMidiVoiceWorkChannelBuffer;

class IMidiVoice;
class IVoiceParams;
class IDrawableModule;
struct ModulationParameters;

enum VoiceType
{
   kVoiceType_Karplus,
   kVoiceType_FM,
   kVoiceType_SingleOscillator,
   kVoiceType_Sampler
};

struct VoiceInfo
{
   VoiceInfo()
   : mPitch(-1)
   , mNoteOn(false)
   {}

   float mPitch;
   IMidiVoice* mVoice;
   double mTime;
   bool mNoteOn;
};

class PolyphonyMgr
{
public:
   PolyphonyMgr(IDrawableModule* owner);
   ~PolyphonyMgr();

   void Init(VoiceType type,
             IVoiceParams* mVoiceParams);

   void Start(double time, int pitch, float amount, int voiceIdx, ModulationParameters modulation);
   void Stop(double time, int pitch);
   void Process(double time, ChannelBuffer* out, int bufferSize);
   void DrawDebug(float x, float y);
   void SetVoiceLimit(int limit) { mVoiceLimit = limit; }
   void KillAll();
   void SetOversampling(int oversampling) { mOversampling = oversampling; }

private:
   VoiceInfo mVoices[kNumVoices];
   bool mAllowStealing;
   int mLastVoice;
   ChannelBuffer mFadeOutBuffer;
   ChannelBuffer mFadeOutWorkBuffer;
   float mWorkBuffer[2048];
   int mFadeOutBufferPos;
   IDrawableModule* mOwner;
   int mVoiceLimit;
   int mOversampling;
};

#endif /* defined(__additiveSynth__PolyphonyMgr__) */
