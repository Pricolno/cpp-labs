#include "bmp.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void print_bmp_err_msg(bmp_err_t bmp_err) {
    switch (bmp_err) {
        case BMP_ERR_MEM_ALLOC:
            fprintf(stderr, "An error occurred during memory allocation.\n");
            break;
        case BMP_ERR_ILLEGAL_ARGS:
            fprintf(stderr, "Illegal arguments were passed to program.\n");
            break;
        case BMP_ERR_FILE_READ:
            fprintf(stderr, "An error occurred during reading input file.\n");
            break;
        case BMP_ERR_FILE_WRITE:
            fprintf(stderr, "An error occurred during writing to output file.\n");
            break;
        default:
            break;
    }
}

int open_file(const char *file_name, const char *readable_name,
                     const char *mode, FILE **in_file) {
    *in_file = fopen(file_name, mode);
    if (!*in_file) {
        fprintf(stderr, "Could not open %s file.\n", readable_name);
        return 1;
    }
    return 0;
}

#define handle_bmp_err(bmp_err) \
        if (bmp_err != BMP_OK) { \
            print_bmp_err_msg(bmp_err); \
            goto error; \
        }

int handle_crop_rotate(int argc, char **argv) {
    if (argc != 8) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }

    char *in_file_name = argv[2];
    char *out_file_name = argv[3];

    bmp_err_t bmp_err;
    bmp_rect_t crop_rect;

    crop_rect.pos.x = atoi(argv[4]);
    crop_rect.pos.y = atoi(argv[5]);
    crop_rect.size.width = atoi(argv[6]);
    crop_rect.size.height = atoi(argv[7]);

    bmp_t *orig = NULL;
    bmp_t *cropped = NULL;
    bmp_t *rotated = NULL;

    FILE *in_file = NULL;
    FILE *out_file = NULL;

    if (open_file(in_file_name, "input", "rb", &in_file) != 0 ||
        open_file(out_file_name, "output", "wb", &out_file) != 0)
        goto error;

    if ((bmp_err = load_bmp(&orig, in_file)) != BMP_OK ||
        (bmp_err = crop_bmp(&cropped, orig, crop_rect)) != BMP_OK ||
        (bmp_err = rotate_bmp(&rotated, cropped, BMP_ROT_CLOCKWISE_90)) != BMP_OK ||
        (bmp_err = save_bmp(rotated, out_file)) != BMP_OK) {

        print_bmp_err_msg(bmp_err);
        goto error;
    }

    int err_code = 0;
    goto clear;

    error:
    err_code = 1;

    clear:
    if (in_file) fclose(in_file);
    if (out_file) fclose(out_file);
    if (orig) free_bmp(orig);
    if (cropped) free_bmp(cropped);
    if (rotated) free_bmp(rotated);

    return err_code;
}


int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Not enough arguments.");
        return 1;
    } else if (strcmp(argv[1], "crop-rotate") == 0) {
        return handle_crop_rotate(argc, argv);
    } else {
        fprintf(stderr, "Unknown command.");
        return 1;
    }
}