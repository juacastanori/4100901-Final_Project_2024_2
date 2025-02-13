#include "main.h"
#include "ring_buffer.h"  

void ring_buffer_init(ring_buffer_t *rb, uint8_t *mem_add, uint8_t capacity) {
    rb->buffer = mem_add;
    rb->capacity = capacity;
    rb->head = 0;
    rb->tail = 0;
    rb->is_full = 0;
}

void ring_buffer_reset(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->is_full = 0;
}

uint8_t ring_buffer_size(ring_buffer_t *rb) {
    if (rb->is_full) {
        return rb->capacity;
    }
    return (rb->head - rb->tail + rb->capacity) % rb->capacity;
}

uint8_t ring_buffer_is_full(ring_buffer_t *rb) {
    return rb->is_full;
}

uint8_t ring_buffer_is_empty(ring_buffer_t *rb) {
    return (!rb->is_full && (rb->head == rb->tail));
}

void ring_buffer_write(ring_buffer_t *rb, uint8_t data) {
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->capacity;

    /* If overwriting */
    if (rb->is_full) {
        rb->tail = (rb->tail + 1) % rb->capacity;
    }

    rb->is_full = (rb->head == rb->tail);
}

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte) {
    if (ring_buffer_is_empty(rb)) {
        return 0;
    }

    *byte = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->is_full = 0;  // Buffer can't be full after a read

    return 1;
}