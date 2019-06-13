./elf_to_ld.sh $ROM_PATH/.output/eagle/release/image/eagle.pro.rom.out >esp32.rom.ld
./elf_to_bootloader_ld.sh $ROM_PATH/.output/eagle/release/image/eagle.pro.rom.out >../../bootloader/subproject/main/esp32c.bootloader.rom.ld
