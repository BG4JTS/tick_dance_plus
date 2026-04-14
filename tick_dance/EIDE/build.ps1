$env:Path = "C:\Users\zzz\.eide\tools\gcc_arm\bin;$env:Path"
$BUILD_DIR = "f:/github/tick_dance/EIDE/build"

if (!(Test-Path $BUILD_DIR)) { New-Item -ItemType Directory -Path $BUILD_DIR -Force }

Write-Host "Compiling C files..." -ForegroundColor Green

$CFLAGS = "-c -mcpu=cortex-m0plus -mthumb -Og -Wall -g -ffunction-sections -fdata-sections --specs=nosys.specs --specs=nano.specs -DUSE_HAL_DRIVER -DPY32F030x8 -If:/github/tick_dance/Inc -If:/github/tick_dance/Drivers/CMSIS/Include -If:/github/tick_dance/Drivers/CMSIS/Device/PY32F0xx/Include -If:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Inc -If:/github/tick_dance/Devices/Inc -If:/github/tick_dance/Fonts -If:/github/tick_dance/ltx/inc -If:/github/tick_dance/ltx/components/app -If:/github/tick_dance/ltx/components/debug -If:/github/tick_dance/ltx/components/event_group -If:/github/tick_dance/ltx/components/lock -If:/github/tick_dance/ltx/components/log -If:/github/tick_dance/ltx/components/script"

$SOURCES = @(
    "f:/github/tick_dance/Src/main.c",
    "f:/github/tick_dance/Src/py32f0xx_hal_msp.c",
    "f:/github/tick_dance/Src/py32f0xx_it.c",
    "f:/github/tick_dance/Src/system_py32f0xx.c",
    "f:/github/tick_dance/Src/myAPP_system.c",
    "f:/github/tick_dance/Src/myAPP_display.c",
    "f:/github/tick_dance/Src/myAPP_device_init.c",
    "f:/github/tick_dance/Src/myAPP_button.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rcc.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rcc_ex.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_flash.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_gpio.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_dma.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_pwr.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_uart.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_spi.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_cortex.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_tim.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_tim_ex.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rtc.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_rtc_ex.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_lptim.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_exti.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_iwdg.c",
    "f:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Src/py32f0xx_hal_wwdg.c",
    "f:/github/tick_dance/Devices/ST7305.c",
    "f:/github/tick_dance/Fonts/num_trans.c",
    "f:/github/tick_dance/Fonts/colon_trans.c",
    "f:/github/tick_dance/ltx/src/ltx.c",
    "f:/github/tick_dance/ltx/components/app/ltx_app.c",
    "f:/github/tick_dance/ltx/components/debug/ltx_cmd.c",
    "f:/github/tick_dance/ltx/components/debug/ltx_param.c",
    "f:/github/tick_dance/ltx/components/event_group/ltx_event_group.c",
    "f:/github/tick_dance/ltx/components/lock/ltx_lock.c",
    "f:/github/tick_dance/ltx/components/log/ltx_log.c",
    "f:/github/tick_dance/ltx/components/log/SEGGER_RTT.c",
    "f:/github/tick_dance/ltx/components/log/SEGGER_RTT_printf.c",
    "f:/github/tick_dance/ltx/components/script/ltx_script.c"
)

$OBJECTS = @()
$i = 0
foreach ($src in $SOURCES) {
    $i++
    $objName = [System.IO.Path]::GetFileNameWithoutExtension($src) + "_" + $i + ".o"
    $objPath = "$BUILD_DIR/$objName"
    $OBJECTS += $objPath
    
    Write-Host "[$i/$($SOURCES.Count)] $([System.IO.Path]::GetFileName($src))"
    $cmd = "arm-none-eabi-gcc.exe $CFLAGS $src -o $objPath"
    Invoke-Expression $cmd
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Error compiling $src" -ForegroundColor Red
        exit 1
    }
}

Write-Host "`nCompiling ASM files..." -ForegroundColor Green
$ASFLAGS = "-c -mcpu=cortex-m0plus -mthumb -Og -DUSE_HAL_DRIVER -DPY32F030x8 -If:/github/tick_dance/Inc -If:/github/tick_dance/Drivers/CMSIS/Include -If:/github/tick_dance/Drivers/CMSIS/Device/PY32F0xx/Include -If:/github/tick_dance/Drivers/PY32F0xx_HAL_Driver/Inc"
$ASM_SRC = "f:/github/tick_dance/EIDE/startup_py32f030xx.s"
$ASM_OBJ = "$BUILD_DIR/startup_py32f030xx.o"
$OBJECTS += $ASM_OBJ

Write-Host "startup_py32f030xx.s"
$cmd = "arm-none-eabi-gcc.exe $ASFLAGS $ASM_SRC -o $ASM_OBJ"
Invoke-Expression $cmd
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error assembling" -ForegroundColor Red
    exit 1
}

Write-Host "`nLinking..." -ForegroundColor Green
$LDSCRIPT = "f:/github/tick_dance/EIDE/py32f030x8.ld"
$OBJ_STRING = $OBJECTS -join " "

# 使用cmd.exe来执行链接命令，避免PowerShell的逗号问题
$LD_ARGS = "-mcpu=cortex-m0plus -mthumb -specs=nano.specs -T $LDSCRIPT -lc -lm -lnosys $OBJ_STRING -Wl,-Map=$BUILD_DIR/Project.map,--cref -Wl,--gc-sections -o $BUILD_DIR/Project.elf"
Start-Process -FilePath "arm-none-eabi-gcc.exe" -ArgumentList $LD_ARGS.Split(' ') -NoNewWindow -Wait
if ($LASTEXITCODE -ne 0) {
    Write-Host "Error linking" -ForegroundColor Red
    exit 1
}

Write-Host "`nGenerating HEX and BIN files..." -ForegroundColor Green
arm-none-eabi-objcopy.exe -O ihex "$BUILD_DIR/Project.elf" "$BUILD_DIR/Project.hex"
arm-none-eabi-objcopy.exe -O binary -S "$BUILD_DIR/Project.elf" "$BUILD_DIR/Project.bin"

Write-Host "`nSize:" -ForegroundColor Green
arm-none-eabi-size.exe "$BUILD_DIR/Project.elf"

Write-Host "`nBuild completed successfully!" -ForegroundColor Green
Write-Host "Output files:" -ForegroundColor Yellow
Write-Host "  ELF: $BUILD_DIR/Project.elf"
Write-Host "  HEX: $BUILD_DIR/Project.hex"
Write-Host "  BIN: $BUILD_DIR/Project.bin"
