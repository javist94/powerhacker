<h1>PowerHacker</h1>
<h2>The world's first hackable, ultra-precise PSU unit (for its cost)</h2>
PowerHacker is a fully featured, dual-channel, python-scriptable PSU unit that counts with an SD card and USB interface. It features an output precision of 2uA at a maximum voltage of 3.3V for its precision channel, or 0.5mA precision @ 24 V (max. current 2.5 A) for its secondary channel. 

<h4>Main features</h4>

  * :snake: Fully scriptable in Python to wait for events and deliever specific curves to the load
  * :memo: Maximum ratings: 2.5 A @ 24V (warning: special cooling required), or 125mA @ 3.3V in precision mode.
  * :moneybag: Cost effective (approx. $23 as of 2022)
  * :computer: USB interface that allows control and data logging from a computer
  * :battery: Short circuit, overload, and overheating integrated protection measures
  * :bulb: Automotive grade, class 5 EMI filtering at the input stage
  * :high_brightness: Double channel output, 16-bit DACs, high quality sigma ADCs, STM32F373 core.
  * :mag: Voltage, current, and power real time metering and logging. Integrated realtime clock.



<h2>How to build the code</h2>
<p>Simply go to the root directory and execute <i>make all -j 4</i>. To flash, execute <i>make flash</i>. If there are any errors, try <i>make clean</i>.</p>
