// Copyright 2024 Khalil Estell
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <libhal-mock/pwm.hpp>

#include <boost/ut.hpp>

namespace hal::mock {
void pwm_mock_test()
{
  using namespace boost::ut;

  "hal::mock::pwm::frequency()"_test = []() {
    // Setup
    constexpr auto expected1 = hertz(1'000);
    constexpr auto expected2 = hertz(10'000);
    hal::mock::pwm mock;
    mock.spy_frequency.trigger_error_on_call(
      3, [&]() { throw hal::operation_not_supported(&mock); });

    // Exercise + Verify
    mock.frequency(expected1);
    expect(expected1 == std::get<0>(mock.spy_frequency.call_history().at(0)));

    mock.frequency(expected2);
    expect(expected2 == std::get<0>(mock.spy_frequency.call_history().at(1)));

    [[maybe_unused]] auto f = throws([&]() { mock.frequency(expected2); });
    expect(expected2 == std::get<0>(mock.spy_frequency.call_history().at(2)));
  };

  "hal::mock::pwm::duty_cycle()"_test = []() {
    // Setup
    constexpr auto expected1 = float(0.5);
    constexpr auto expected2 = float(0.25);
    hal::mock::pwm mock;
    mock.spy_duty_cycle.trigger_error_on_call(
      3, [&]() { throw hal::operation_not_supported(&mock); });

    // Exercise + Verify
    mock.duty_cycle(expected1);
    expect(expected1 == std::get<0>(mock.spy_duty_cycle.call_history().at(0)));

    mock.duty_cycle(expected2);
    expect(expected2 == std::get<0>(mock.spy_duty_cycle.call_history().at(1)));

    [[maybe_unused]] auto f = throws([&]() { mock.duty_cycle(expected2); });
    expect(expected2 == std::get<0>(mock.spy_duty_cycle.call_history().at(2)));
  };
};
}  // namespace hal::mock
