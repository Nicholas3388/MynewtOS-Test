/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include "flash_map.h"
#include "native_bsp.h"

static struct flash_area bsp_flash_areas[] = {
    [FLASH_AREA_BOOTLOADER] = {
        .fa_flash_id = 0,       /* internal flash */
        .fa_off = 0x00000000,   /* beginning */
        .fa_size = (16 * 1024)
    },
    /* 2 * 16K and 1*64K sectors here */
    [FLASH_AREA_IMAGE_0] = {
        .fa_flash_id = 0,
        .fa_off = 0x00020000,
        .fa_size = (384 * 1024)
    },
    [FLASH_AREA_IMAGE_1] = {
        .fa_flash_id = 0,
        .fa_off = 0x00080000,
        .fa_size = (384 * 1024)
    },
    [FLASH_AREA_IMAGE_SCRATCH] = {
        .fa_flash_id = 0,
        .fa_off = 0x000e0000,
        .fa_size = (128 * 1024)
    },
    [FLASH_AREA_NFFS] = {
        .fa_flash_id = 0,
        .fa_off = 0x00008000,
        .fa_size = (32 * 1024)
    },
    [FLASH_AREA_REBOOT_LOG] = {
        .fa_flash_id = 0,
        .fa_off = 0x00004000,
        .fa_size = (16 * 1024)
    },
};

/*
 * Returns the flash map slot where the currently active image is located.
 * If executing from internal flash from fixed location, that slot would
 * be easy to find.
 * If images are in external flash, and copied to RAM for execution, then
 * this routine would have to figure out which one of those slots is being
 * used.
 */
int
bsp_imgr_current_slot(void)
{
    return FLASH_AREA_IMAGE_0;
}

void
bsp_init(void)
{
    flash_area_init(bsp_flash_areas,
      sizeof(bsp_flash_areas) / sizeof(bsp_flash_areas[0]));
}
