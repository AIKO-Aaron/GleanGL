typedef enum {
    SPHERE = 0,
    PLANE,
	CUBE,
	LIGHT_SPHERE
} objectType;

typedef struct __attribute__ ((packed)) {
    objectType type;
    float4 color;
    float4 position;
    float4 meta1, meta2;
} object;

typedef struct {
    float4 position; // Position of intersection
    float4 normal;
    float distance;
    bool wasHit;
    object obj;
    
} objectIntersection;
