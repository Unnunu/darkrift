#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

void *mem_alloc(s32 size, const char *file, s32 line);
void mem_free(void *);
s32 cont_init(s32);
void func_800027A0(void);
s32 get_free_mem(ChunkHeader *arg0);
void dma_read_noblock(s32 romAddr, void *vramAddr, s32 size);
void dma_read(s32 romAddr, void *vramAddr, s32 size);
s32 func_80000EA8(s32 size);
void func_80000F70(s32 arg0);
void func_8002A8C0(UnkItemAlpha *arg0, u32 arg1, u32 arg2);
void func_80000E0C(u8 *arg0, u8 arg1, u32 arg2);
Object *func_80015FB4(s32);
void func_80015C58(Object *);
void func_800213E0(s32, u32);
void func_80021918(Object *arg0, s32 arg1);
void func_800217A0(Object *, s32);
void func_80012A20(UnkMu *arg0, UnkMu *arg1, s32 arg2, s32 arg3);
void func_8001305C(Matrix4f *, Vec3s *);
void func_800136CC(Matrix4f *, Vec3i *);
void func_80015724(Object *);
void func_800263A8(void);
void asset_open_folder(char *path, s32 context);
Texture *load_background(char *, s32, s32, s32, s32, s32, s32);
Object *create_worker(void (*)(Object *), s16);
void func_80019DE4(Object *);
void func_80001D88(void);
void func_8002630C(s32 arg0);
void func_80002178(s32 arg0, Quad *arg1);
void func_80018AD0(Object *);
Object *func_8002BBD4(Vec3i *arg0, SpriteDef *arg1, s32 arg2);
u32 asset_find(char *name, s32 context);
void str_concat(char *dst, char *src);
void str_copy(char *arg0, char *arg1);
void func_800149F0(Matrix4f *, Matrix4f *, Matrix4f *);
Object *obj_allocate(s16 arg0);
void func_80012AA8(Matrix4f *mf);
void func_8001370C(Vec4i *arg0, Vec3s *arg1);
void func_80038DE0(Object *);
void func_80038B10(Object *);
void func_800371C0(Object *);
void func_80037500(Object *);
void func_8003635C(Object *);
void func_80013A54(Mtx *, Matrix4f *);
s16 func_80012518(s32 arg0, s32 arg1);

#endif
