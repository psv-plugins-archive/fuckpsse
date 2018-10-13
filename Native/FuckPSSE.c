
#include <taihen.h>
#include <vitasdk.h>
#include <string.h>
#include <stdio.h>



SceUID sceKernelGetStdout();

static SceUID LoadModuleHook;
static tai_hook_ref_t LoadModuleHook_ref;

static SceUID cOpenHook;
static tai_hook_ref_t cOpenHook_ref;

static SceUID cReadHook;
static tai_hook_ref_t cReadHook_ref;

static SceUID OpenHook;
static tai_hook_ref_t OpenHook_ref;

static char LetsJustAttackILL[0x1200] = {0x4D,0x5A,0x90,0x00,0x03,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0xB8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x0E,0x1F,0xBA,0x0E,0x00,0xB4,0x09,0xCD,0x21,0xB8,0x01,0x4C,0xCD,0x21,0x54,0x68,0x69,0x73,0x20,0x70,0x72,0x6F,0x67,0x72,0x61,0x6D,0x20,0x63,0x61,0x6E,0x6E,0x6F,0x74,0x20,0x62,0x65,0x20,0x72,0x75,0x6E,0x20,0x69,0x6E,0x20,0x44,0x4F,0x53,0x20,0x6D,0x6F,0x64,0x65,0x2E,0x0D,0x0D,0x0A,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x45,0x00,0x00,0x4C,0x01,0x03,0x00,0xB4,0xEF,0xC1,0x5B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x02,0x01,0x0B,0x01,0x0B,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x8E,0x27,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x20,0x00,0x00,0x00,0x02,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x40,0x85,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x27,0x00,0x00,0x53,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0xC8,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x20,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2E,0x74,0x65,0x78,0x74,0x00,0x00,0x00,0x94,0x07,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x60,0x2E,0x72,0x73,0x72,0x63,0x00,0x00,0x00,0xC8,0x04,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x40,0x2E,0x72,0x65,0x6C,0x6F,0x63,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x02,0x00,0x05,0x00,0xE4,0x21,0x00,0x00,0x54,0x05,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x30,0x05,0x00,0x0F,0x01,0x00,0x00,0x01,0x00,0x00,0x11,0x00,0x28,0x02,0x00,0x00,0x06,0x00,0x72,0x01,0x00,0x00,0x70,0x72,0x1B,0x00,0x00,0x70,0x17,0x28,0x03,0x00,0x00,0x0A,0x0A,0x72,0x01,0x00,0x00,0x70,0x72,0x1B,0x00,0x00,0x70,0x17,0x28,0x04,0x00,0x00,0x0A,0x0B,0x00,0x06,0x13,0x05,0x16,0x13,0x06,0x2B,0x2E,0x11,0x05,0x11,0x06,0x9A,0x0C,0x00,0x00,0x08,0x72,0x1F,0x00,0x00,0x70,0x72,0x37,0x00,0x00,0x70,0x6F,0x05,0x00,0x00,0x0A,0x28,0x06,0x00,0x00,0x0A,0x26,0x00,0xDE,0x05,0x26,0x00,0x00,0xDE,0x00,0x00,0x00,0x11,0x06,0x17,0x58,0x13,0x06,0x11,0x06,0x11,0x05,0x8E,0x69,0xFE,0x04,0x13,0x07,0x11,0x07,0x2D,0xC4,0x00,0x07,0x13,0x05,0x16,0x13,0x06,0x2B,0x6F,0x11,0x05,0x11,0x06,0x9A,0x0D,0x00,0x28,0x07,0x00,0x00,0x0A,0x00,0x28,0x03,0x00,0x00,0x06,0x00,0x7E,0x01,0x00,0x00,0x04,0x22,0x00,0x00,0x80,0x3F,0x22,0x00,0x00,0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x6F,0x08,0x00,0x00,0x0A,0x00,0x7E,0x01,0x00,0x00,0x04,0x6F,0x09,0x00,0x00,0x0A,0x00,0x7E,0x01,0x00,0x00,0x04,0x6F,0x0A,0x00,0x00,0x0A,0x00,0x09,0x28,0x0B,0x00,0x00,0x0A,0x13,0x04,0x09,0x72,0x1F,0x00,0x00,0x70,0x72,0x37,0x00,0x00,0x70,0x6F,0x05,0x00,0x00,0x0A,0x11,0x04,0x28,0x0C,0x00,0x00,0x0A,0x00,0x00,0x11,0x06,0x17,0x58,0x13,0x06,0x11,0x06,0x11,0x05,0x8E,0x69,0xFE,0x04,0x13,0x07,0x11,0x07,0x2D,0x83,0x2B,0x14,0x00,0x28,0x07,0x00,0x00,0x0A,0x00,0x28,0x03,0x00,0x00,0x06,0x00,0x28,0x04,0x00,0x00,0x06,0x00,0x00,0x17,0x13,0x07,0x2B,0xE7,0x00,0x01,0x10,0x00,0x00,0x00,0x00,0x39,0x00,0x1A,0x53,0x00,0x05,0x0B,0x00,0x00,0x01,0x32,0x00,0x73,0x0D,0x00,0x00,0x0A,0x80,0x01,0x00,0x00,0x04,0x2A,0x00,0x00,0x00,0x13,0x30,0x01,0x00,0x09,0x00,0x00,0x00,0x02,0x00,0x00,0x11,0x00,0x16,0x28,0x0E,0x00,0x00,0x0A,0x0A,0x2A,0xDE,0x00,0x7E,0x01,0x00,0x00,0x04,0x22,0x00,0x00,0x00,0x00,0x22,0x00,0x00,0x80,0x3F,0x22,0x00,0x00,0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x6F,0x08,0x00,0x00,0x0A,0x00,0x7E,0x01,0x00,0x00,0x04,0x6F,0x09,0x00,0x00,0x0A,0x00,0x7E,0x01,0x00,0x00,0x04,0x6F,0x0A,0x00,0x00,0x0A,0x00,0x2A,0x1E,0x02,0x28,0x0F,0x00,0x00,0x0A,0x2A,0x00,0x00,0x00,0x42,0x53,0x4A,0x42,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x76,0x32,0x2E,0x30,0x2E,0x35,0x30,0x37,0x32,0x37,0x00,0x00,0x00,0x00,0x05,0x00,0x6C,0x00,0x00,0x00,0xB4,0x01,0x00,0x00,0x23,0x7E,0x00,0x00,0x20,0x02,0x00,0x00,0x30,0x02,0x00,0x00,0x23,0x53,0x74,0x72,0x69,0x6E,0x67,0x73,0x00,0x00,0x00,0x00,0x50,0x04,0x00,0x00,0x64,0x00,0x00,0x00,0x23,0x55,0x53,0x00,0xB4,0x04,0x00,0x00,0x10,0x00,0x00,0x00,0x23,0x47,0x55,0x49,0x44,0x00,0x00,0x00,0xC4,0x04,0x00,0x00,0x90,0x00,0x00,0x00,0x23,0x42,0x6C,0x6F,0x62,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x57,0x15,0x02,0x00,0x09,0x00,0x00,0x00,0x00,0xFA,0x25,0x33,0x00,0x16,0x00,0x00,0x01,0x00,0x00,0x00,0x0D,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x0A,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x2F,0x00,0x28,0x00,0x0A,0x00,0x69,0x00,0x4B,0x00,0x06,0x00,0xCB,0x00,0xAB,0x00,0x06,0x00,0xEB,0x00,0xAB,0x00,0x06,0x00,0x17,0x01,0x0D,0x01,0x06,0x00,0x21,0x01,0x0D,0x01,0x06,0x00,0x46,0x01,0x28,0x00,0x06,0x00,0x55,0x01,0x0D,0x01,0x0A,0x00,0x94,0x01,0x73,0x01,0x06,0x00,0xCD,0x01,0x0D,0x01,0x06,0x00,0xED,0x01,0x28,0x00,0x0A,0x00,0x12,0x02,0xF7,0x01,0x0A,0x00,0x1A,0x02,0xF7,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x00,0x12,0x00,0x1A,0x00,0x05,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x79,0x00,0x0A,0x00,0x50,0x20,0x00,0x00,0x00,0x00,0x96,0x00,0x82,0x00,0x0E,0x00,0x01,0x00,0x7C,0x21,0x00,0x00,0x00,0x00,0x96,0x00,0x87,0x00,0x14,0x00,0x02,0x00,0x8C,0x21,0x00,0x00,0x00,0x00,0x96,0x00,0x92,0x00,0x14,0x00,0x02,0x00,0xA1,0x21,0x00,0x00,0x00,0x00,0x96,0x00,0x99,0x00,0x14,0x00,0x02,0x00,0xD9,0x21,0x00,0x00,0x00,0x00,0x86,0x18,0xA0,0x00,0x18,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0xA6,0x00,0x19,0x00,0xA0,0x00,0x1C,0x00,0x21,0x00,0xA0,0x00,0x18,0x00,0x29,0x00,0x2E,0x01,0x21,0x00,0x29,0x00,0x3D,0x01,0x21,0x00,0x39,0x00,0x4D,0x01,0x2A,0x00,0x29,0x00,0x63,0x01,0x30,0x00,0x49,0x00,0xA1,0x01,0x14,0x00,0x11,0x00,0xAD,0x01,0x36,0x00,0x11,0x00,0xBB,0x01,0x18,0x00,0x11,0x00,0xC1,0x01,0x18,0x00,0x51,0x00,0xD2,0x01,0x3E,0x00,0x51,0x00,0xDF,0x01,0x44,0x00,0x11,0x00,0xA0,0x00,0x18,0x00,0x61,0x00,0x26,0x02,0x5A,0x00,0x09,0x00,0xA0,0x00,0x18,0x00,0x2E,0x00,0x0B,0x00,0x65,0x00,0x2E,0x00,0x13,0x00,0x6E,0x00,0x4B,0x00,0x60,0x00,0x04,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x01,0x00,0x00,0x02,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x4D,0x6F,0x64,0x75,0x6C,0x65,0x3E,0x00,0x61,0x70,0x70,0x2E,0x65,0x78,0x65,0x00,0x41,0x70,0x70,0x4D,0x61,0x69,0x6E,0x00,0x64,0x75,0x6D,0x70,0x00,0x6D,0x73,0x63,0x6F,0x72,0x6C,0x69,0x62,0x00,0x53,0x79,0x73,0x74,0x65,0x6D,0x00,0x4F,0x62,0x6A,0x65,0x63,0x74,0x00,0x53,0x63,0x65,0x2E,0x50,0x6C,0x61,0x79,0x53,0x74,0x61,0x74,0x69,0x6F,0x6E,0x2E,0x43,0x6F,0x72,0x65,0x00,0x53,0x63,0x65,0x2E,0x50,0x6C,0x61,0x79,0x53,0x74,0x61,0x74,0x69,0x6F,0x6E,0x2E,0x43,0x6F,0x72,0x65,0x2E,0x47,0x72,0x61,0x70,0x68,0x69,0x63,0x73,0x00,0x47,0x72,0x61,0x70,0x68,0x69,0x63,0x73,0x43,0x6F,0x6E,0x74,0x65,0x78,0x74,0x00,0x67,0x72,0x61,0x70,0x68,0x69,0x63,0x73,0x00,0x4D,0x61,0x69,0x6E,0x00,0x49,0x6E,0x69,0x74,0x69,0x61,0x6C,0x69,0x7A,0x65,0x00,0x55,0x70,0x64,0x61,0x74,0x65,0x00,0x52,0x65,0x6E,0x64,0x65,0x72,0x00,0x2E,0x63,0x74,0x6F,0x72,0x00,0x61,0x72,0x67,0x73,0x00,0x53,0x79,0x73,0x74,0x65,0x6D,0x2E,0x52,0x75,0x6E,0x74,0x69,0x6D,0x65,0x2E,0x43,0x6F,0x6D,0x70,0x69,0x6C,0x65,0x72,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x00,0x43,0x6F,0x6D,0x70,0x69,0x6C,0x61,0x74,0x69,0x6F,0x6E,0x52,0x65,0x6C,0x61,0x78,0x61,0x74,0x69,0x6F,0x6E,0x73,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x52,0x75,0x6E,0x74,0x69,0x6D,0x65,0x43,0x6F,0x6D,0x70,0x61,0x74,0x69,0x62,0x69,0x6C,0x69,0x74,0x79,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x61,0x70,0x70,0x00,0x53,0x79,0x73,0x74,0x65,0x6D,0x2E,0x49,0x4F,0x00,0x44,0x69,0x72,0x65,0x63,0x74,0x6F,0x72,0x79,0x00,0x53,0x65,0x61,0x72,0x63,0x68,0x4F,0x70,0x74,0x69,0x6F,0x6E,0x00,0x47,0x65,0x74,0x44,0x69,0x72,0x65,0x63,0x74,0x6F,0x72,0x69,0x65,0x73,0x00,0x47,0x65,0x74,0x46,0x69,0x6C,0x65,0x73,0x00,0x53,0x74,0x72,0x69,0x6E,0x67,0x00,0x52,0x65,0x70,0x6C,0x61,0x63,0x65,0x00,0x44,0x69,0x72,0x65,0x63,0x74,0x6F,0x72,0x79,0x49,0x6E,0x66,0x6F,0x00,0x43,0x72,0x65,0x61,0x74,0x65,0x44,0x69,0x72,0x65,0x63,0x74,0x6F,0x72,0x79,0x00,0x53,0x63,0x65,0x2E,0x50,0x6C,0x61,0x79,0x53,0x74,0x61,0x74,0x69,0x6F,0x6E,0x2E,0x43,0x6F,0x72,0x65,0x2E,0x45,0x6E,0x76,0x69,0x72,0x6F,0x6E,0x6D,0x65,0x6E,0x74,0x00,0x53,0x79,0x73,0x74,0x65,0x6D,0x45,0x76,0x65,0x6E,0x74,0x73,0x00,0x43,0x68,0x65,0x63,0x6B,0x45,0x76,0x65,0x6E,0x74,0x73,0x00,0x53,0x65,0x74,0x43,0x6C,0x65,0x61,0x72,0x43,0x6F,0x6C,0x6F,0x72,0x00,0x43,0x6C,0x65,0x61,0x72,0x00,0x53,0x77,0x61,0x70,0x42,0x75,0x66,0x66,0x65,0x72,0x73,0x00,0x46,0x69,0x6C,0x65,0x00,0x52,0x65,0x61,0x64,0x41,0x6C,0x6C,0x42,0x79,0x74,0x65,0x73,0x00,0x57,0x72,0x69,0x74,0x65,0x41,0x6C,0x6C,0x42,0x79,0x74,0x65,0x73,0x00,0x45,0x78,0x63,0x65,0x70,0x74,0x69,0x6F,0x6E,0x00,0x53,0x63,0x65,0x2E,0x50,0x6C,0x61,0x79,0x53,0x74,0x61,0x74,0x69,0x6F,0x6E,0x2E,0x43,0x6F,0x72,0x65,0x2E,0x49,0x6E,0x70,0x75,0x74,0x00,0x47,0x61,0x6D,0x65,0x50,0x61,0x64,0x00,0x47,0x61,0x6D,0x65,0x50,0x61,0x64,0x44,0x61,0x74,0x61,0x00,0x47,0x65,0x74,0x44,0x61,0x74,0x61,0x00,0x00,0x00,0x00,0x19,0x2F,0x00,0x41,0x00,0x70,0x00,0x70,0x00,0x6C,0x00,0x69,0x00,0x63,0x00,0x61,0x00,0x74,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x03,0x2A,0x00,0x00,0x17,0x41,0x00,0x70,0x00,0x70,0x00,0x6C,0x00,0x69,0x00,0x63,0x00,0x61,0x00,0x74,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x2B,0x44,0x00,0x6F,0x00,0x63,0x00,0x75,0x00,0x6D,0x00,0x65,0x00,0x6E,0x00,0x74,0x00,0x73,0x00,0x2F,0x00,0x41,0x00,0x70,0x00,0x70,0x00,0x6C,0x00,0x69,0x00,0x63,0x00,0x61,0x00,0x74,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0xF7,0x6B,0x51,0xB7,0x1D,0xBC,0x44,0x48,0xB7,0x05,0x01,0x74,0xF7,0x2B,0x35,0x8B,0x00,0x08,0x79,0x43,0x9F,0xFC,0x30,0x8A,0xA6,0xA0,0x03,0x06,0x12,0x09,0x05,0x00,0x01,0x01,0x1D,0x0E,0x03,0x00,0x00,0x01,0x03,0x20,0x00,0x01,0x04,0x20,0x01,0x01,0x08,0x08,0x00,0x03,0x1D,0x0E,0x0E,0x0E,0x11,0x19,0x05,0x20,0x02,0x0E,0x0E,0x0E,0x05,0x00,0x01,0x12,0x21,0x0E,0x07,0x20,0x04,0x01,0x0C,0x0C,0x0C,0x0C,0x05,0x00,0x01,0x1D,0x05,0x0E,0x06,0x00,0x02,0x01,0x0E,0x1D,0x05,0x0E,0x07,0x08,0x1D,0x0E,0x1D,0x0E,0x0E,0x0E,0x1D,0x05,0x1D,0x0E,0x08,0x02,0x05,0x00,0x01,0x11,0x35,0x08,0x04,0x07,0x01,0x11,0x35,0x08,0x01,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x1E,0x01,0x00,0x01,0x00,0x54,0x02,0x16,0x57,0x72,0x61,0x70,0x4E,0x6F,0x6E,0x45,0x78,0x63,0x65,0x70,0x74,0x69,0x6F,0x6E,0x54,0x68,0x72,0x6F,0x77,0x73,0x01,0x00,0x00,0x00,0x60,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x27,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x43,0x6F,0x72,0x45,0x78,0x65,0x4D,0x61,0x69,0x6E,0x00,0x6D,0x73,0x63,0x6F,0x72,0x65,0x65,0x2E,0x64,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0xFF,0x25,0x00,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x10,0x00,0x00,0x00,0x20,0x00,0x00,0x80,0x18,0x00,0x00,0x00,0x38,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x50,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x68,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x90,0x00,0x00,0x00,0xA0,0x40,0x00,0x00,0x34,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x42,0x00,0x00,0xEA,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34,0x02,0x34,0x00,0x00,0x00,0x56,0x00,0x53,0x00,0x5F,0x00,0x56,0x00,0x45,0x00,0x52,0x00,0x53,0x00,0x49,0x00,0x4F,0x00,0x4E,0x00,0x5F,0x00,0x49,0x00,0x4E,0x00,0x46,0x00,0x4F,0x00,0x00,0x00,0x00,0x00,0xBD,0x04,0xEF,0xFE,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x00,0x00,0x01,0x00,0x56,0x00,0x61,0x00,0x72,0x00,0x46,0x00,0x69,0x00,0x6C,0x00,0x65,0x00,0x49,0x00,0x6E,0x00,0x66,0x00,0x6F,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x04,0x00,0x00,0x00,0x54,0x00,0x72,0x00,0x61,0x00,0x6E,0x00,0x73,0x00,0x6C,0x00,0x61,0x00,0x74,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0x04,0x94,0x01,0x00,0x00,0x01,0x00,0x53,0x00,0x74,0x00,0x72,0x00,0x69,0x00,0x6E,0x00,0x67,0x00,0x46,0x00,0x69,0x00,0x6C,0x00,0x65,0x00,0x49,0x00,0x6E,0x00,0x66,0x00,0x6F,0x00,0x00,0x00,0x70,0x01,0x00,0x00,0x01,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x34,0x00,0x62,0x00,0x30,0x00,0x00,0x00,0x2C,0x00,0x02,0x00,0x01,0x00,0x46,0x00,0x69,0x00,0x6C,0x00,0x65,0x00,0x44,0x00,0x65,0x00,0x73,0x00,0x63,0x00,0x72,0x00,0x69,0x00,0x70,0x00,0x74,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x30,0x00,0x08,0x00,0x01,0x00,0x46,0x00,0x69,0x00,0x6C,0x00,0x65,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x08,0x00,0x01,0x00,0x49,0x00,0x6E,0x00,0x74,0x00,0x65,0x00,0x72,0x00,0x6E,0x00,0x61,0x00,0x6C,0x00,0x4E,0x00,0x61,0x00,0x6D,0x00,0x65,0x00,0x00,0x00,0x61,0x00,0x70,0x00,0x70,0x00,0x2E,0x00,0x65,0x00,0x78,0x00,0x65,0x00,0x00,0x00,0x28,0x00,0x02,0x00,0x01,0x00,0x4C,0x00,0x65,0x00,0x67,0x00,0x61,0x00,0x6C,0x00,0x43,0x00,0x6F,0x00,0x70,0x00,0x79,0x00,0x72,0x00,0x69,0x00,0x67,0x00,0x68,0x00,0x74,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x38,0x00,0x08,0x00,0x01,0x00,0x4F,0x00,0x72,0x00,0x69,0x00,0x67,0x00,0x69,0x00,0x6E,0x00,0x61,0x00,0x6C,0x00,0x46,0x00,0x69,0x00,0x6C,0x00,0x65,0x00,0x6E,0x00,0x61,0x00,0x6D,0x00,0x65,0x00,0x00,0x00,0x61,0x00,0x70,0x00,0x70,0x00,0x2E,0x00,0x65,0x00,0x78,0x00,0x65,0x00,0x00,0x00,0x34,0x00,0x08,0x00,0x01,0x00,0x50,0x00,0x72,0x00,0x6F,0x00,0x64,0x00,0x75,0x00,0x63,0x00,0x74,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x00,0x00,0x38,0x00,0x08,0x00,0x01,0x00,0x41,0x00,0x73,0x00,0x73,0x00,0x65,0x00,0x6D,0x00,0x62,0x00,0x6C,0x00,0x79,0x00,0x20,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6F,0x00,0x6E,0x00,0x00,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x2E,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0xBB,0xBF,0x3C,0x3F,0x78,0x6D,0x6C,0x20,0x76,0x65,0x72,0x73,0x69,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22,0x20,0x65,0x6E,0x63,0x6F,0x64,0x69,0x6E,0x67,0x3D,0x22,0x55,0x54,0x46,0x2D,0x38,0x22,0x20,0x73,0x74,0x61,0x6E,0x64,0x61,0x6C,0x6F,0x6E,0x65,0x3D,0x22,0x79,0x65,0x73,0x22,0x3F,0x3E,0x0D,0x0A,0x3C,0x61,0x73,0x73,0x65,0x6D,0x62,0x6C,0x79,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x6D,0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,0x2D,0x63,0x6F,0x6D,0x3A,0x61,0x73,0x6D,0x2E,0x76,0x31,0x22,0x20,0x6D,0x61,0x6E,0x69,0x66,0x65,0x73,0x74,0x56,0x65,0x72,0x73,0x69,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x22,0x3E,0x0D,0x0A,0x20,0x20,0x3C,0x61,0x73,0x73,0x65,0x6D,0x62,0x6C,0x79,0x49,0x64,0x65,0x6E,0x74,0x69,0x74,0x79,0x20,0x76,0x65,0x72,0x73,0x69,0x6F,0x6E,0x3D,0x22,0x31,0x2E,0x30,0x2E,0x30,0x2E,0x30,0x22,0x20,0x6E,0x61,0x6D,0x65,0x3D,0x22,0x4D,0x79,0x41,0x70,0x70,0x6C,0x69,0x63,0x61,0x74,0x69,0x6F,0x6E,0x2E,0x61,0x70,0x70,0x22,0x2F,0x3E,0x0D,0x0A,0x20,0x20,0x3C,0x74,0x72,0x75,0x73,0x74,0x49,0x6E,0x66,0x6F,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x6D,0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,0x2D,0x63,0x6F,0x6D,0x3A,0x61,0x73,0x6D,0x2E,0x76,0x32,0x22,0x3E,0x0D,0x0A,0x20,0x20,0x20,0x20,0x3C,0x73,0x65,0x63,0x75,0x72,0x69,0x74,0x79,0x3E,0x0D,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x3C,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x65,0x64,0x50,0x72,0x69,0x76,0x69,0x6C,0x65,0x67,0x65,0x73,0x20,0x78,0x6D,0x6C,0x6E,0x73,0x3D,0x22,0x75,0x72,0x6E,0x3A,0x73,0x63,0x68,0x65,0x6D,0x61,0x73,0x2D,0x6D,0x69,0x63,0x72,0x6F,0x73,0x6F,0x66,0x74,0x2D,0x63,0x6F,0x6D,0x3A,0x61,0x73,0x6D,0x2E,0x76,0x33,0x22,0x3E,0x0D,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3C,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x65,0x64,0x45,0x78,0x65,0x63,0x75,0x74,0x69,0x6F,0x6E,0x4C,0x65,0x76,0x65,0x6C,0x20,0x6C,0x65,0x76,0x65,0x6C,0x3D,0x22,0x61,0x73,0x49,0x6E,0x76,0x6F,0x6B,0x65,0x72,0x22,0x20,0x75,0x69,0x41,0x63,0x63,0x65,0x73,0x73,0x3D,0x22,0x66,0x61,0x6C,0x73,0x65,0x22,0x2F,0x3E,0x0D,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x3C,0x2F,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x65,0x64,0x50,0x72,0x69,0x76,0x69,0x6C,0x65,0x67,0x65,0x73,0x3E,0x0D,0x0A,0x20,0x20,0x20,0x20,0x3C,0x2F,0x73,0x65,0x63,0x75,0x72,0x69,0x74,0x79,0x3E,0x0D,0x0A,0x20,0x20,0x3C,0x2F,0x74,0x72,0x75,0x73,0x74,0x49,0x6E,0x66,0x6F,0x3E,0x0D,0x0A,0x3C,0x2F,0x61,0x73,0x73,0x65,0x6D,0x62,0x6C,0x79,0x3E,0x0D,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x0C,0x00,0x00,0x00,0x90,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int HasReplacedExe = 0;

//Thanks dots-tb for reversing this!
typedef struct PSM_handle {
uint32_t unk0;
uint32_t unk1;
uint32_t filesz;
uint32_t unk3;

} PSM_handle;

char OldPath[1024];

int pss_crypto_open_p(PSM_handle *handle, char *path) {
	memset(OldPath,0x00,1024);
	memcpy(OldPath,path,1024);
	
	sceClibPrintf("[FuckPSSE] [OPEN] before run: PSM_handle:\n");
	sceClibPrintf("[FuckPSSE] unk0 %lx\n",handle->unk0);
	sceClibPrintf("[FuckPSSE] unk1 %lx\n",handle->unk1);
	sceClibPrintf("[FuckPSSE] Size %lx\n",handle->filesz);
	sceClibPrintf("[FuckPSSE] unk3 %lx\n",handle->unk3);
	sceClibPrintf("[FuckPSSE] Path: %s\n",path);
	
	int ret;
	ret = TAI_CONTINUE(int, cOpenHook_ref, handle, path);
	
	if(!strcmp(OldPath,"pss0:/top/Application/app.exe") && !HasReplacedExe)
	{
		handle->filesz = 0x1200;
	}
	
	sceClibPrintf("[FuckPSSE] [OPEN] after run: PSM_handle:\n");
	sceClibPrintf("[FuckPSSE] unk0 %lx\n",handle->unk0);
	sceClibPrintf("[FuckPSSE] unk1 %lx\n",handle->unk1);
	sceClibPrintf("[FuckPSSE] Size %lx\n",handle->filesz);
	sceClibPrintf("[FuckPSSE] unk3 %lx\n",handle->unk3);
	sceClibPrintf("[FuckPSSE] Path: %s\n",path);
	sceClibPrintf("[FuckPSSE] ret: %x\n",ret);

	return ret;
}

char *pss_crypto_read_p(PSM_handle *handle, int ctx) {
	sceClibPrintf("[FuckPSSE] [READ] before run: PSM_handle:\n");
	sceClibPrintf("[FuckPSSE] unk0 %lx\n",handle->unk0);
	sceClibPrintf("[FuckPSSE] unk1 %lx\n",handle->unk1);
	sceClibPrintf("[FuckPSSE] Size %lx\n",handle->filesz);
	sceClibPrintf("[FuckPSSE] unk3 %lx\n",handle->unk3);
	sceClibPrintf("[FuckPSSE] Path: %x\n",ctx);
	
	if(!strcmp(OldPath,"pss0:/top/Application/app.exe") && !HasReplacedExe)
	{
		TAI_CONTINUE(int, cReadHook_ref, handle, ctx);
		sceClibPrintf("[FuckPSSE] APP.EXE Detected! Injecting dumper!\n");
		HasReplacedExe = 1;
		return (char*)&LetsJustAttackILL;
	}
	else
	{
	int ret;
	ret = TAI_CONTINUE(int, cReadHook_ref, handle, ctx);
	
	sceClibPrintf("[FuckPSSE] [READ] after run: PSM_handle:\n");
	sceClibPrintf("[FuckPSSE] unk0 %lx\n",handle->unk0);
	sceClibPrintf("[FuckPSSE] unk1 %lx\n",handle->unk1);
	sceClibPrintf("[FuckPSSE] Size %lx\n",handle->filesz);
	sceClibPrintf("[FuckPSSE] unk3 %lx\n",handle->unk3);
	sceClibPrintf("[FuckPSSE] Path: %x\n",ctx);
	
	return ret;
	}
	return 0;
}

int pss_io_open_p(int arg1, int arg2, int arg3) {
	sceClibPrintf("[FuckPSSE] Before Run:  pss_io_open() %x %x %x \n",arg1,arg2,arg3);
	int ret;
	ret = TAI_CONTINUE(int, OpenHook_ref, arg1, arg2, arg3);
	sceClibPrintf("[FuckPSSE] After Run pss_io_open() %x %x %x ret: %x\n",arg1,arg2,arg3 ,ret);
	return ret;
}


SceUID sceKernelLoadStartModule_p(char *path, SceSize args, void *argp, int flags, SceKernelLMOption *option, int *status)
{
	//sceClibPrintf("[FuckPSSE] Starting Module: %s\n",path);
	
	SceUID ret;
	ret = TAI_CONTINUE(SceUID, LoadModuleHook_ref, path, args, argp, flags, option, status);
	
	if(!strcmp(path,"app0:/module/libpsm.suprx"))
	{
		sceClibPrintf("[FuckPSSE] SceLibPsm Detected!\n");
		cOpenHook = taiHookFunctionImport(&cOpenHook_ref, 
										  "SceLibMono",
										  TAI_ANY_LIBRARY, 
										  0x6B4125E4, //pss_crypto_open
										  pss_crypto_open_p);
								  
		cReadHook = taiHookFunctionImport(&cReadHook_ref, 
										  "SceLibMono",
										  TAI_ANY_LIBRARY, 
										  0x32BA8444, //pss_crypto_read
										  pss_crypto_read_p);

		sceClibPrintf("[FuckPSSE] cOpenHook %x, %x\n",cOpenHook,cOpenHook_ref);
		sceClibPrintf("[FuckPSSE] cReadHook %x, %x\n",cReadHook,cReadHook_ref);

	
	}
	return ret;
}


void _start() __attribute__ ((weak, alias ("module_start"))); 

void module_start(SceSize argc, const void *args) {
	char titleid[12];
	sceAppMgrAppParamGetString(0, 12, titleid, 256);

	if(!strcmp(titleid,"PCSI00011")) // PSM Runtime
	{
		sceClibPrintf("[FuckPSSE] Silca: I like to see girls die :3\n");
		sceClibPrintf("[FuckPSSE] Loaded!\n");
		sceClibPrintf("[FuckPSSE] Running on %s\n",titleid);

		LoadModuleHook = taiHookFunctionImport(&LoadModuleHook_ref, 
										  TAI_MAIN_MODULE,
										  TAI_ANY_LIBRARY,
										  0x2DCC4AFA, //sceKernelLoadStartModule
										  sceKernelLoadStartModule_p);

		sceClibPrintf("[FuckPSSE] LoadModuleHook %x, %x\n",LoadModuleHook,LoadModuleHook_ref);
	}
}

int module_stop(SceSize argc, const void *args) {

	// release hooks
	if (cOpenHook >= 0) taiHookRelease(cOpenHook, cOpenHook_ref);
	if (cReadHook >= 0) taiHookRelease(cReadHook, cReadHook_ref);
	if (OpenHook >= 0) taiHookRelease(LoadModuleHook, LoadModuleHook_ref);
	return SCE_KERNEL_STOP_SUCCESS;
}