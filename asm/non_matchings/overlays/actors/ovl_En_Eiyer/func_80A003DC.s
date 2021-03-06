glabel func_80A003DC
/* 0043C 80A003DC 27BDFFD0 */  addiu   $sp, $sp, 0xFFD0           ## $sp = FFFFFFD0
/* 00440 80A003E0 44802000 */  mtc1    $zero, $f4                 ## $f4 = 0.00
/* 00444 80A003E4 AFB00020 */  sw      $s0, 0x0020($sp)
/* 00448 80A003E8 AFA50034 */  sw      $a1, 0x0034($sp)
/* 0044C 80A003EC 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00450 80A003F0 AFBF0024 */  sw      $ra, 0x0024($sp)
/* 00454 80A003F4 3C050600 */  lui     $a1, 0x0600                ## $a1 = 06000000
/* 00458 80A003F8 24A50704 */  addiu   $a1, $a1, 0x0704           ## $a1 = 06000704
/* 0045C 80A003FC 2484014C */  addiu   $a0, $a0, 0x014C           ## $a0 = 0000014C
/* 00460 80A00400 0C02947A */  jal     SkelAnime_ChangeAnimDefaultStop
/* 00464 80A00404 E484FF1C */  swc1    $f4, -0x00E4($a0)          ## 00000068
/* 00468 80A00408 3C0EFFCF */  lui     $t6, 0xFFCF                ## $t6 = FFCF0000
/* 0046C 80A0040C 35CEFFFF */  ori     $t6, $t6, 0xFFFF           ## $t6 = FFCFFFFF
/* 00470 80A00410 AE0E02A8 */  sw      $t6, 0x02A8($s0)           ## 000002A8
/* 00474 80A00414 26020024 */  addiu   $v0, $s0, 0x0024           ## $v0 = 00000024
/* 00478 80A00418 8C580000 */  lw      $t8, 0x0000($v0)           ## 00000024
/* 0047C 80A0041C 3C014282 */  lui     $at, 0x4282                ## $at = 42820000
/* 00480 80A00420 44813000 */  mtc1    $at, $f6                   ## $f6 = 65.00
/* 00484 80A00424 AE18027C */  sw      $t8, 0x027C($s0)           ## 0000027C
/* 00488 80A00428 8C4F0004 */  lw      $t7, 0x0004($v0)           ## 00000028
/* 0048C 80A0042C 8E080004 */  lw      $t0, 0x0004($s0)           ## 00000004
/* 00490 80A00430 920A0299 */  lbu     $t2, 0x0299($s0)           ## 00000299
/* 00494 80A00434 AE0F0280 */  sw      $t7, 0x0280($s0)           ## 00000280
/* 00498 80A00438 8C580008 */  lw      $t8, 0x0008($v0)           ## 0000002C
/* 0049C 80A0043C 3C014416 */  lui     $at, 0x4416                ## $at = 44160000
/* 004A0 80A00440 861900B6 */  lh      $t9, 0x00B6($s0)           ## 000000B6
/* 004A4 80A00444 44814000 */  mtc1    $at, $f8                   ## $f8 = 600.00
/* 004A8 80A00448 35091000 */  ori     $t1, $t0, 0x1000           ## $t1 = 00001000
/* 004AC 80A0044C 314BFFFE */  andi    $t3, $t2, 0xFFFE           ## $t3 = 00000000
/* 004B0 80A00450 AE090004 */  sw      $t1, 0x0004($s0)           ## 00000004
/* 004B4 80A00454 A20B0299 */  sb      $t3, 0x0299($s0)           ## 00000299
/* 004B8 80A00458 E60600C4 */  swc1    $f6, 0x00C4($s0)           ## 000000C4
/* 004BC 80A0045C AE180284 */  sw      $t8, 0x0284($s0)           ## 00000284
/* 004C0 80A00460 A6190032 */  sh      $t9, 0x0032($s0)           ## 00000032
/* 004C4 80A00464 E60800BC */  swc1    $f8, 0x00BC($s0)           ## 000000BC
/* 004C8 80A00468 AFA2002C */  sw      $v0, 0x002C($sp)
/* 004CC 80A0046C 02002025 */  or      $a0, $s0, $zero            ## $a0 = 00000000
/* 004D0 80A00470 0C00BE0A */  jal     Audio_PlayActorSound2

/* 004D4 80A00474 240538C2 */  addiu   $a1, $zero, 0x38C2         ## $a1 = 000038C2
/* 004D8 80A00478 240C0001 */  addiu   $t4, $zero, 0x0001         ## $t4 = 00000001
/* 004DC 80A0047C 240D02BC */  addiu   $t5, $zero, 0x02BC         ## $t5 = 000002BC
/* 004E0 80A00480 AFAD0014 */  sw      $t5, 0x0014($sp)
/* 004E4 80A00484 AFAC0010 */  sw      $t4, 0x0010($sp)
/* 004E8 80A00488 8FA40034 */  lw      $a0, 0x0034($sp)
/* 004EC 80A0048C 8FA5002C */  lw      $a1, 0x002C($sp)
/* 004F0 80A00490 00003025 */  or      $a2, $zero, $zero          ## $a2 = 00000000
/* 004F4 80A00494 0C00A527 */  jal     EffectSsGSplash_Spawn
/* 004F8 80A00498 00003825 */  or      $a3, $zero, $zero          ## $a3 = 00000000
/* 004FC 80A0049C 3C0E80A0 */  lui     $t6, %hi(func_80A00B18)    ## $t6 = 80A00000
/* 00500 80A004A0 25CE0B18 */  addiu   $t6, $t6, %lo(func_80A00B18) ## $t6 = 80A00B18
/* 00504 80A004A4 AE0E0190 */  sw      $t6, 0x0190($s0)           ## 00000190
/* 00508 80A004A8 8FBF0024 */  lw      $ra, 0x0024($sp)
/* 0050C 80A004AC 8FB00020 */  lw      $s0, 0x0020($sp)
/* 00510 80A004B0 27BD0030 */  addiu   $sp, $sp, 0x0030           ## $sp = 00000000
/* 00514 80A004B4 03E00008 */  jr      $ra
/* 00518 80A004B8 00000000 */  nop
