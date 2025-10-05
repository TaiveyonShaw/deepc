#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ubyte-reader.c"

int main() {
    // Load training images
    ImageData *train_images = read_ubyte_images("../dataset/train-images.idx3-ubyte");
    if (!train_images) {
        return 1;
    }

    // Load training labels
    LabelData *train_labels = read_ubyte_labels("../dataset/train-labels.idx1-ubyte");
    if (!train_labels) {
        free_image_data(train_images);
        return 1;
    }

    printf("Number of images: %u\n", train_images->num_images);
    printf("Image dimensions: %u x %u\n", train_images->rows, train_images->cols);
    printf("Number of labels: %u\n", train_labels->num_labels);

    // Access specific image pixel: train_images->data[image_idx * rows * cols + row * cols + col]
    // Access specific label: train_labels->labels[label_idx]

    // Example: Print first label
    for (int i = 1; i < (train_images->rows * train_images->cols) + 1; i++) {
        if (i % 28) {
            printf("%u ", train_images->data[i-1]);
        }
        else {
            printf("%u\n", train_images->data[i-1]);
        }
    }

    // Clean up
    free_image_data(train_images);
    free_label_data(train_labels);

    return 0;
}
