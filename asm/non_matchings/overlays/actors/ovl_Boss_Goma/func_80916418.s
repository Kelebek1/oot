glabel func_80916418
/* 00A08 80916418 27BDFFD0 */  addiu   $sp, $sp, 0xFFD0           ## $sp = FFFFFFD0
/* 00A0C 8091641C AFB00028 */  sw      $s0, 0x0028($sp)
/* 00A10 80916420 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00A14 80916424 AFBF002C */  sw      $ra, 0x002C($sp)
/* 00A18 80916428 3C040600 */  lui     $a0, 0x0600                ## $a0 = 06000000
/* 00A1C 8091642C 0C028800 */  jal     SkelAnime_GetFrameCount

/* 00A20 80916430 24842360 */  addiu   $a0, $a0, 0x2360           ## $a0 = 06002360
/* 00A24 80916434 44822000 */  mtc1    $v0, $f4                   ## $f4 = 0.00
/* 00A28 80916438 44800000 */  mtc1    $zero, $f0                 ## $f0 = 0.00
/* 00A2C 8091643C 3C01C0A0 */  lui     $at, 0xC0A0                ## $at = C0A00000
/* 00A30 80916440 468021A0 */  cvt.s.w $f6, $f4
/* 00A34 80916444 44814000 */  mtc1    $at, $f8                   ## $f8 = -5.00
/* 00A38 80916448 3C050600 */  lui     $a1, 0x0600                ## $a1 = 06000000
/* 00A3C 8091644C 44070000 */  mfc1    $a3, $f0
/* 00A40 80916450 24A52360 */  addiu   $a1, $a1, 0x2360           ## $a1 = 06002360
/* 00A44 80916454 2604014C */  addiu   $a0, $s0, 0x014C           ## $a0 = 0000014C
/* 00A48 80916458 E7A60010 */  swc1    $f6, 0x0010($sp)
/* 00A4C 8091645C 3C063F80 */  lui     $a2, 0x3F80                ## $a2 = 3F800000
/* 00A50 80916460 AFA00014 */  sw      $zero, 0x0014($sp)
/* 00A54 80916464 0C029468 */  jal     SkelAnime_ChangeAnim

/* 00A58 80916468 E7A80018 */  swc1    $f8, 0x0018($sp)
/* 00A5C 8091646C 44800000 */  mtc1    $zero, $f0                 ## $f0 = 0.00
/* 00A60 80916470 3C0E8092 */  lui     $t6, %hi(func_80919A40)    ## $t6 = 80920000
/* 00A64 80916474 25CE9A40 */  addiu   $t6, $t6, %lo(func_80919A40) ## $t6 = 80919A40
/* 00A68 80916478 AE0E0190 */  sw      $t6, 0x0190($s0)           ## 00000190
/* 00A6C 8091647C 2404001E */  addiu   $a0, $zero, 0x001E         ## $a0 = 0000001E
/* 00A70 80916480 2405003C */  addiu   $a1, $zero, 0x003C         ## $a1 = 0000003C
/* 00A74 80916484 E6000068 */  swc1    $f0, 0x0068($s0)           ## 00000068
/* 00A78 80916488 E6000060 */  swc1    $f0, 0x0060($s0)           ## 00000060
/* 00A7C 8091648C 0C01DF64 */  jal     Math_Rand_S16Offset

/* 00A80 80916490 E600006C */  swc1    $f0, 0x006C($s0)           ## 0000006C
/* 00A84 80916494 A60201D2 */  sh      $v0, 0x01D2($s0)           ## 000001D2
/* 00A88 80916498 8FBF002C */  lw      $ra, 0x002C($sp)
/* 00A8C 8091649C 8FB00028 */  lw      $s0, 0x0028($sp)
/* 00A90 809164A0 27BD0030 */  addiu   $sp, $sp, 0x0030           ## $sp = 00000000
/* 00A94 809164A4 03E00008 */  jr      $ra
/* 00A98 809164A8 00000000 */  nop