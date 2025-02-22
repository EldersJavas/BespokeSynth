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
/*
  ==============================================================================

    UserPrefsEditor.h
    Created: 12 Feb 2021 10:29:53pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "Slider.h"
#include "TextEntry.h"
#include "DropdownList.h"
#include "ClickButton.h"
#include "RadioButton.h"
#include "UserPrefs.h"

class UserPrefsEditor : public IDrawableModule, public IFloatSliderListener, public IIntSliderListener, public ITextEntryListener, public IDropdownListener, public IButtonListener, public IRadioButtonListener
{
public:
   UserPrefsEditor();
   ~UserPrefsEditor();
   static IDrawableModule* Create() { return new UserPrefsEditor(); }

   void CreateUIControls() override;

   bool AlwaysOnTop() override { return true; }
   bool CanMinimize() override { return false; }
   bool IsSingleton() const override { return true; }

   void Show();
   void CreatePrefsFileIfNonexistent();

   void CheckboxUpdated(Checkbox* checkbox) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void IntSliderUpdated(IntSlider* slider, int oldVal) override;
   void TextEntryComplete(TextEntry* entry) override;
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   void ButtonClicked(ClickButton* button) override;
   void RadioButtonUpdated(RadioButton* radio, int oldVal) override;

   bool IsSaveable() override { return false; }
   std::vector<IUIControl*> ControlsToNotSetDuringLoadState() const override;
   std::vector<IUIControl*> ControlsToIgnoreInSaveState() const override;

private:
   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return true; }
   void GetModuleDimensions(float& width, float& height) override
   {
      width = mWidth;
      height = mHeight;
   }

   void UpdateDropdowns(std::vector<DropdownList*> toUpdate);
   void DrawRightLabel(IUIControl* control, std::string text, ofColor color, float offsetX = 12);
   void CleanUpSave(std::string& json);
   bool PrefRequiresRestart(UserPref* pref) const;
   void Save();

   UserPrefCategory mCategory{ UserPrefCategory::General };
   RadioButton* mCategorySelector;
   ClickButton* mSaveButton;
   ClickButton* mCancelButton;

   float mWidth;
   float mHeight;
};
