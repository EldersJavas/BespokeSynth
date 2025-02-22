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
//  ControlTactileFeedback.h
//  modularSynth
//
//  Created by Ryan Challinor on 1/9/14.
//
//

#ifndef __modularSynth__ControlTactileFeedback__
#define __modularSynth__ControlTactileFeedback__

#include <iostream>
#include "IAudioSource.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "Slider.h"

class ControlTactileFeedback : public IAudioSource, public IDrawableModule, public IFloatSliderListener
{
public:
   ControlTactileFeedback();
   ~ControlTactileFeedback();
   static IDrawableModule* Create() { return new ControlTactileFeedback(); }


   void CreateUIControls() override;

   //IAudioSource
   void Process(double time) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }


   void CheckboxUpdated(Checkbox* checkbox) override {}

   //IFloatSliderListener
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}

   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;

private:
   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return mEnabled; }
   void GetModuleDimensions(float& width, float& height) override
   {
      width = 80;
      height = 60;
   }

   float mPhase;
   float mPhaseInc;


   float mVolume;
   FloatSlider* mVolumeSlider;
};


#endif /* defined(__modularSynth__ControlTactileFeedback__) */
