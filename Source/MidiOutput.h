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
//  MidiOutput.h
//  Bespoke
//
//  Created by Ryan Challinor on 5/24/15.
//
//

#ifndef __Bespoke__MidiOutput__
#define __Bespoke__MidiOutput__

#include <iostream>
#include "MidiDevice.h"
#include "IDrawableModule.h"
#include "INoteReceiver.h"
#include "DropdownList.h"
#include "Transport.h"

class IAudioSource;

class MidiOutputModule : public IDrawableModule, public INoteReceiver, public IDropdownListener, public IAudioPoller
{
public:
   MidiOutputModule();
   virtual ~MidiOutputModule();
   static IDrawableModule* Create() { return new MidiOutputModule(); }


   void CreateUIControls() override;

   void Init() override;

   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   void SendCC(int control, int value, int voiceIdx = -1) override;

   //IAudioPoller
   void OnTransportAdvanced(float amount) override;

   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void DropdownClicked(DropdownList* list) override;

   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;

private:
   void InitController();
   void BuildControllerList();

   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return true; }
   void GetModuleDimensions(float& w, float& h) override
   {
      w = 190;
      h = 25;
   }

   int mControllerIndex;
   DropdownList* mControllerList;

   MidiDevice mDevice;

   int mChannel;
   bool mUseVoiceAsChannel;
   float mPitchBendRange;
   int mModwheelCC;

   struct ChannelModulations
   {
      ModulationParameters mModulation;
      float mLastPitchBend;
      float mLastModWheel;
      float mLastPressure;
   };

   std::vector<ChannelModulations> mChannelModulations;
};

#endif /* defined(__Bespoke__MidiOutput__) */
