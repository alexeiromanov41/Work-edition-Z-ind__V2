SET PATH=D:\Keil_v5\ARM\ARMCLANG\Bin;D:\Program Files\Python311\Scripts\;D:\Program Files\Python311\;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Intel\Shared Libraries\redist\intel64\compiler;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\dotnet\;D:\Program Files (x86)\serialplot\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;D:\Program Files\Git\cmd;C:\Program Files (x86)\IVI Foundation\IVI\bin;C:\Program Files\IVI Foundation\IVI\bin;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\Win64\Bin\;C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Bin;C:\Users\i8960\AppData\Local\Microsoft\WindowsApps;C:\Users\i8960\.dotnet\tools;D:\Users\i8960\AppData\Local\Programs\Microsoft VS Code\bin;D:\msys64\mingw64\bin;
SET CPU_TYPE=STM32F405RGTx
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=CubeMX
SET CPU_CLOCK=0x007A1200
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\startup_stm32f405xx._ac"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\main.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\gpio.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\adc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\dma.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\spi.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\tim.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_it.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_msp.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\crc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_adc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_adc_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_ll_adc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_rcc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_rcc_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_flash.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_flash_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_flash_ramfunc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_gpio.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_dma_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_dma.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_pwr.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_pwr_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_cortex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_exti.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_spi.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_tim.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_tim_ex.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\stm32f4xx_hal_crc.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\system_stm32f4xx.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\soft.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @"cubemx\25lc040a.__i"
"D:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via "CubeMX\CubeMX.lnp"
"D:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" "CubeMX\CubeMX.axf" --i32combined --output "CubeMX\CubeMX.hex"
