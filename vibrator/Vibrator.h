/*
** Copyright 2023, The LineageOS Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#pragma once

#include <aidl/android/hardware/vibrator/BnVibrator.h>

#define INTENSITY_MIN 12
#define INTENSITY_MAX 127
#define INTENSITY_DEFAULT INTENSITY_MAX

#define AMPLITUDE_LIGHT 0.25
#define AMPLITUDE_MEDIUM 0.5
#define AMPLITUDE_STRONG 1

#define VIBRATOR_TIMEOUT_PATH "/sys/class/timed_output/vibrator/enable"
#define VIBRATOR_INTENSITY_PATH "/sys/class/timed_output/vibrator/vtg_level"

using ::aidl::android::hardware::vibrator::IVibratorCallback;
using ::aidl::android::hardware::vibrator::Braking;
using ::aidl::android::hardware::vibrator::Effect;
using ::aidl::android::hardware::vibrator::EffectStrength;
using ::aidl::android::hardware::vibrator::CompositeEffect;
using ::aidl::android::hardware::vibrator::CompositePrimitive;
using ::aidl::android::hardware::vibrator::PrimitivePwle;

namespace aidl {
namespace android {
namespace hardware {
namespace vibrator {

class Vibrator : public BnVibrator {
public:
    Vibrator();
    ndk::ScopedAStatus getCapabilities(int32_t* _aidl_return) override;
    ndk::ScopedAStatus off() override;
    ndk::ScopedAStatus on(int32_t timeoutMs, const std::shared_ptr<IVibratorCallback>& callback) override;
    ndk::ScopedAStatus perform(Effect effect, EffectStrength strength, const std::shared_ptr<IVibratorCallback>& callback, int32_t* _aidl_return) override;
    ndk::ScopedAStatus getSupportedEffects(std::vector<Effect>* _aidl_return) override;
    ndk::ScopedAStatus setAmplitude(float amplitude) override;
    ndk::ScopedAStatus setExternalControl(bool enabled) override;
    ndk::ScopedAStatus getCompositionDelayMax(int32_t* _aidl_return) override;
    ndk::ScopedAStatus getCompositionSizeMax(int32_t* _aidl_return) override;
    ndk::ScopedAStatus getSupportedPrimitives(std::vector<CompositePrimitive>* _aidl_return) override;
    ndk::ScopedAStatus getPrimitiveDuration(CompositePrimitive primitive, int32_t* _aidl_return) override;
    ndk::ScopedAStatus compose(const std::vector<CompositeEffect>& composite, const std::shared_ptr<IVibratorCallback>& callback) override;
    ndk::ScopedAStatus getSupportedAlwaysOnEffects(std::vector<Effect>* _aidl_return) override;
    ndk::ScopedAStatus alwaysOnEnable(int32_t id, Effect effect, EffectStrength strength) override;
    ndk::ScopedAStatus alwaysOnDisable(int32_t id) override;
    ndk::ScopedAStatus getResonantFrequency(float* _aidl_return) override;
    ndk::ScopedAStatus getQFactor(float* _aidl_return) override;
    ndk::ScopedAStatus getFrequencyResolution(float* _aidl_return) override;
    ndk::ScopedAStatus getFrequencyMinimum(float* _aidl_return) override;
    ndk::ScopedAStatus getBandwidthAmplitudeMap(std::vector<float>* _aidl_return) override;
    ndk::ScopedAStatus getPwlePrimitiveDurationMax(int32_t* _aidl_return) override;
    ndk::ScopedAStatus getPwleCompositionSizeMax(int32_t* _aidl_return) override;
    ndk::ScopedAStatus getSupportedBraking(std::vector<Braking>* _aidl_return) override;
    ndk::ScopedAStatus composePwle(const std::vector<PrimitivePwle>& composite, const std::shared_ptr<IVibratorCallback>& callback) override;

private:
    ndk::ScopedAStatus activate(uint32_t ms);
    static uint32_t effectToMs(Effect effect, ndk::ScopedAStatus* status);
    static float strengthToAmplitude(EffectStrength strength, ndk::ScopedAStatus* status);

    bool mEnabled{false};
    bool mExternalControl{false};
    std::mutex mMutex;

    bool mIsTimedOutVibrator;
    bool mHasTimedOutIntensity;
};

} // namespace vibrator
} // namespace hardware
} // namespace android
} // namespace aidl
