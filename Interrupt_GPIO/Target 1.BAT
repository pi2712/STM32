SET PATH=C:\Keil_v5\ARM\ARMCLANG\Bin;C:\Program Files\Common Files\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Users\quanv\AppData\Local\Programs\Python\Python312;C:\Users\quanv\AppData\Local\Programs\Python\Python312\Scripts;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;C:\Users\quanv\AppData\Local\Programs\Python\Launcher;C:\Program Files\Cloudflare\Cloudflare WARP\;C:\Program Files\Git\cmd;C:\Program Files\Java\jdk-21\bin;C:\Program Files\MATLAB\R2017b\runtime\win64;C:\Program Files\MATLAB\R2017b\bin;C:\Users\quanv\AppData\Local\Programs\Python\Launcher\;C:\Users\quanv\AppData\Local\Microsoft\WindowsApps;C:\Users\quanv\AppData\Local\Programs\Microsoft VS Code\bin;C:\MinGW\bin;C:\Users\quanv\AppData\Local\GitHubDesktop\bin
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\main.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\delay.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\gpio.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\exti.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\startup_stm32f10x_md._ac"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\system_stm32f10x.__i"
"C:\Keil_v5\ARM\ARMCLANG\Bin\ArmLink" --Via ".\Objects\project.lnp"
"C:\Keil_v5\ARM\ARMCLANG\Bin\fromelf.exe" ".\Objects\project.axf" --i32combined --output ".\Objects\project.hex"
