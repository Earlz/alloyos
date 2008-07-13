#ifndef X86_H
#define X86_H

#include <stdint.h>

void Interrupt(uint8_t num);

inline unsigned char inportb(unsigned int port);
inline void outportb(unsigned int port,unsigned char value);
inline void stopints();
inline void startints();
inline void SetDS(unsigned short seg);
inline void SetES(unsigned short seg);
inline void SetFS(unsigned short seg);
inline void SetGS(unsigned short seg);
inline void SetSS(unsigned short seg);
inline void SetCS(unsigned short seg,void *where);
inline unsigned short GetDS();
inline unsigned short GetES();
inline unsigned short GetGS();
inline unsigned short GetFS();
inline unsigned short GetSS();
inline unsigned short GetCS();

inline void hlt();







#endif


