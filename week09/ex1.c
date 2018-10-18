#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <zconf.h>
#include <time.h>
#include <stdlib.h>

#define IterateFrames(i, n_frames)  for (int i = 0; i < n_frames; i++)

int hits;
int misses;
int report_mode;

static int AGING_ONE = 1 << (sizeof(char) * 8 - 1); // Int to add when updating counters, depending on char size

typedef struct {
    unsigned char counter;
    int n;
    char R;
} FRAME;

/**
 * Find an available slot or the least important page in given table of page frames
 * @param frames given table of page frames
 * @param n_frames number of frames
 * @return
 */
int find_place(FRAME *frames, int n_frames) {
    unsigned char least_counter = 255;
    int least_counter_index = -1;

    IterateFrames(i, n_frames) {
        if (frames[i].n == -1) {
            return i;
        }
        if (frames[i].counter < least_counter) {
            least_counter = frames[i].counter;
            least_counter_index = i;
        }
    }
    return least_counter_index;
}

/**
 * Initialize given frame with specified attributes
 * @param frame given frame
 * @param n custom N
 * @param R custom Referenced bit
 */
void init_frame(FRAME *frame, int n, char R) {
    frame->n = n;
    frame->counter = 0;
    frame->R = R;
}

/**
 * Make given frame empty
 * @param frame given frame
 */
void flush_frame(FRAME *frame) {
    init_frame(frame, -1, 0);
}

/**
 * Request a page with given number from table of page frames
 * @param frames page frames table
 * @param n_frames how many frames are in the table
 * @param n given number
 */
void get(FRAME *frames, int n_frames, int n) {
    if (report_mode >= 1)
        printf("\n\nRequesting page %d...\n", n);
    IterateFrames(i, n_frames) {
        if (frames[i].n == n) {
            hits++;
            frames[i].R = 1;
            if (report_mode >= 1)
                printf("Page %d found in frame %d\n", n, i);
            return;
        }
    }
    if (report_mode >= 1)
        printf("Page %d not found. Fetching...\n", n);
    misses++;
    int i = find_place(frames, n_frames);
    if (report_mode >= 1)
        printf("Page %d fetched to frame %d [N: %d, counter: %d, R: %d]\n", n, i, frames[i].n, frames[i].counter,
               frames[i].R);
    init_frame(&frames[i], n, 1);
}

/**
 * Update counters and R bits in given table of page frames
 * @param frames given table of page frames
 * @param n_frames number of frames in table
 */
void aging(FRAME *frames, int n_frames) {
    IterateFrames(i, n_frames) {
        if (frames[i].n != -1) {
            frames[i].counter >>= 1;
            if (frames[i].R != 0) {
                frames[i].counter |= AGING_ONE;
                frames[i].R = 0;
            }
        }
    }
}

/**
 * Print all frames of given table
 * @param frames given table
 * @param n_frames number of frames
 */
void dump_frames(FRAME *frames, int n_frames) {
    printf("\nHit/miss: %d/%d", hits, misses);
    printf("\nFrame\tN   \tCounter\tReferenced\n");
    IterateFrames(i, n_frames) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i, frames[i].n, frames[i].counter, frames[i].R);
        fflush(stdout);
    }
}

/**
 * Initialize new table of page frames
 * @param n_frames number of page frames
 * @return
 */
FRAME *init_frames_table(int n_frames) {
    FRAME *frames = malloc(n_frames * sizeof(FRAME));
    IterateFrames(i, n_frames) {
        flush_frame(&frames[i]);
    }
    return frames;
}


int main() {
    FILE *input;
    input = fopen("../input.txt", "r");

    if (input == NULL) {
        printf("File not found!");
        return 1;
    }

    int n_frames = 0;
    int requested_page;

    printf("How many page frames do you want: ");
    scanf("%d", &n_frames);

    printf("Select report mode (0 - only hit/miss report (default), 1 - with comments, 2 - comments & page dump on every step): ");
    scanf("%d", &report_mode);

    FRAME *table = init_frames_table(n_frames);

    srand(time(NULL));

    while (fscanf(input, "%d", &requested_page) != EOF) {
        get(table, n_frames, requested_page);

        if (report_mode == 2)
            dump_frames(table, n_frames);

        // Aging triggered here
        if (1) { // Can be replaced with either time-based condition on something else

            if (report_mode >= 1)
                printf("\n*IRQ* One clock passed...\n");

            aging(table, n_frames);
        }
    }

    printf("\n\nSummary:\n\tHit/miss: %d/%d\n", hits, misses);

    return 0;
}