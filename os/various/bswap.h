#ifndef BSWAP_H
#define BSWAP_H

#if defined(__cplusplus)
extern "C" {
#endif

#if !(defined(ARCH_BIG_ENDIAN) || defined(ARCH_LITTLE_ENDIAN))
#error "ARCH_BIG_ENDIAN or ARCH_LITTLE_ENDIAN not set."
#endif

#if defined(ARCH_BIG_ENDIAN) && defined(ARCH_LITTLE_ENDIAN)
#error "ARCH_BIG_ENDIAN and ARCH_LITTLE_ENDIAN are both set."
#endif

    
#define BSWAP_16(x)							\
    (uint16_t)((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))
#define BSWAP_32(x)							\
    (uint32_t)((((x) & 0xFF000000UL) >> 24UL) |				\
	       (((x) & 0x00FF0000UL) >>  8UL) |				\
	       (((x) & 0x0000FF00UL) <<  8UL) |				\
	       (((x) & 0x000000FFUL) << 24UL))

    
#if defined(ARCH_BIG_ENDIAN)
#define le16_to_cpu(x)           bswap_16(x)
#define le32_to_cpu(x)           bswap_32(x)
#define be16_to_cpu(x)           (x)
#define be32_to_cpu(x)           (x)
#define cpu_to_le16(x)           bswap_16(x)
#define cpu_to_le32(x)           bswap_32(x)
#define cpu_to_be16(x)           (x)
#define cpu_to_be32(x)           (x)
#define LE16_TO_CPU(x)           BSWAP_16(x)
#define LE32_TO_CPU(x)           BSWAP_32(x)
#define BE16_TO_CPU(x)           (x)
#define BE32_TO_CPU(x)           (x)
#define CPU_TO_LE16(x)           BSWAP_16(x)
#define CPU_TO_LE32(x)           BSWAP_32(x)
#define CPU_TO_BE16(x)           (x)
#define CPU_TO_BE32(x)           (x)
#endif

   
#if defined(ARCH_LITTLE_ENDIAN)
#define le16_to_cpu(x)           (x)
#define le32_to_cpu(x)           (x)
#define be16_to_cpu(x)           bswap_16(x)
#define be32_to_cpu(x)           bswap_32(x)
#define cpu_to_le16(x)           (x)
#define cpu_to_le32(x)           (x)
#define cpu_to_be16(x)           bswap_16(x)
#define cpu_to_be32(x)           bswap_32(x)
#define LE16_TO_CPU(x)           (x)
#define LE32_TO_CPU(x)           (x)
#define BE16_TO_CPU(x)           BSWAP_16(x)
#define BE32_TO_CPU(x)           BSWAP_32(x)
#define CPU_TO_LE16(x)           (x)
#define CPU_TO_LE32(x)           (x)
#define CPU_TO_BE16(x)           BSWAP_16(x)
#define CPU_TO_BE32(x)           BSWAP_32(x)
#endif
    
    
static inline uint16_t bswap_16(const uint16_t x)
    __attribute__ ((warn_unused_result))
    __attribute__ ((const))
    __attribute__ ((always_inline));

static inline uint16_t bswap_16(const uint16_t x) {
    if (__builtin_constant_p(x))
	return BSWAP_16(x);

    uint8_t                             tmp;
    union { uint16_t x; uint8_t b[2]; } data;
    
    data.x    = x;
    tmp       = data.b[0];
    data.b[0] = data.b[1];
    data.b[1] = tmp;
    
    return data.x;
}

static inline uint32_t bswap_32(const uint32_t x)
    __attribute__ ((warn_unused_result))
    __attribute__ ((const))
    __attribute__ ((always_inline));


static inline uint32_t bswap_32(const uint32_t x) {
    if (__builtin_constant_p(x))
	return BSWAP_32(x);
    
    uint8_t                             tmp;
    union { uint32_t x; uint8_t b[4]; } data;
    
    data.x    = x;    
    tmp       = data.b[0];
    data.b[0] = data.b[3];
    data.b[3] = tmp;
    tmp       = data.b[1];
    data.b[1] = data.b[2];
    data.b[2] = tmp;
    
    return data.x;
}
    
static inline void bswap_n(void* const data, uint8_t len)
    __attribute__ ((nonnull (1)));

static inline void bswap_n(void* const data, uint8_t len) {
    uint8_t* ptr = (uint8_t*)data;

    for ( ; len > 1 ; ptr++, len -= 2 ) {
	uint8_t tmp = *ptr;
	*ptr            = *(ptr + len - 1);
	*(ptr + len - 1) = tmp;
    }
}
    
#if defined(__cplusplus)
}
#endif

#endif


