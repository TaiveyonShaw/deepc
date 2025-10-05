#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    uint16_t num_images;
    uint16_t rows;
    uint16_t cols;
} ImageData;

typedef struct {
    uint8_t *labels;
    uint16_t num_labels;
} LabelData;

// Read 16-bit big-endian integer
uint16_t read_uint16(FILE *fp) {
    uint8_t bytes[4];
    fread(bytes, sizeof(uint8_t), 4, fp);
    return ((uint16_t)bytes[0] << 24) |
           ((uint16_t)bytes[1] << 16) |
           ((uint16_t)bytes[2] << 8)  |
           ((uint16_t)bytes[3]);
}

// Read ubyte image file
ImageData* read_ubyte_images(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    ImageData *img_data = (ImageData*)malloc(sizeof(ImageData));
    if (!img_data) {
        fclose(fp);
        return NULL;
    }

    // Read header
    uint16_t magic = read_uint16(fp);
    img_data->num_images = read_uint16(fp);
    img_data->rows = read_uint16(fp);
    img_data->cols = read_uint16(fp);

    // Allocate memory for image data
    size_t data_size = img_data->num_images * img_data->rows * img_data->cols;
    img_data->data = (uint8_t*)malloc(data_size * sizeof(uint8_t));
    if (!img_data->data) {
        free(img_data);
        fclose(fp);
        return NULL;
    }

    // Read image data
    size_t read_count = fread(img_data->data, sizeof(uint8_t), data_size, fp);
    if (read_count != data_size) {
        fprintf(stderr, "Error: Could not read all image data\n");
        free(img_data->data);
        free(img_data);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return img_data;
}

// Read ubyte label file
LabelData* read_ubyte_labels(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    LabelData *label_data = (LabelData*)malloc(sizeof(LabelData));
    if (!label_data) {
        fclose(fp);
        return NULL;
    }

    // Read header
    uint16_t magic = read_uint16(fp);
    label_data->num_labels = read_uint16(fp);

    // Allocate memory for label data
    label_data->labels = (uint8_t*)malloc(label_data->num_labels * sizeof(uint8_t));
    if (!label_data->labels) {
        free(label_data);
        fclose(fp);
        return NULL;
    }

    // Read label data
    size_t read_count = fread(label_data->labels, sizeof(uint8_t), label_data->num_labels, fp);
    if (read_count != label_data->num_labels) {
        fprintf(stderr, "Error: Could not read all label data\n");
        free(label_data->labels);
        free(label_data);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return label_data;
}

// Free image data
void free_image_data(ImageData *img_data) {
    if (img_data) {
        if (img_data->data) free(img_data->data);
        free(img_data);
    }
}

// Free label data
void free_label_data(LabelData *label_data) {
    if (label_data) {
        if (label_data->labels) free(label_data->labels);
        free(label_data);
    }
}
