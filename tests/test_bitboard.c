#include "test.h"
#include "bitboard.h"

int main(void)
{
        uint64_t bb = BB_1;
        uint64_t bb_out;
        enum {LEN_INDICES = 64};
        int indices[LEN_INDICES];
        uint64_t masks[LEN_INDICES];
        int rank, file;

        bb |= BB_1 << 20; /* set up bitboard to have a piece on H8 and D3 */

        ASSERT(bb_get_piece_indices(bb, indices, 6) == -1, "get piece indices fail");
        ASSERT(bb_get_piece_indices(bb, indices, LEN_INDICES) == 2, "get piece indices pass");
        ASSERT(indices[0] == 63, "check H8 index");
        ASSERT(indices[1] == 43, "check D3 index");

        ASSERT(bb_get_rank_file_from_index(43, &rank, &file) == 0, "get rank file pass");
        ASSERT(rank == 2, "D3 rank");
        ASSERT(file == 3, "D3 file");
        ASSERT(bb_get_rank_file_from_index(64, &rank, &file) == 1, "get rank file fail");

        ASSERT(bb_get_num_pieces(bb) == 2, "get number of pieces");

        ASSERT(bb_split_masks(bb, masks, 63) == -1, "split masks fail");
        ASSERT(bb_split_masks(bb, masks, LEN_INDICES) == 2, "split masks pass");
        ASSERT(masks[0] == BB_1 << 0, "split masks H8 index");
        ASSERT(masks[1] == BB_1 << 20, "split masks D3 index");

        ASSERT(bb_merge_masks(&bb_out, masks, 0) == 0, "merge masks length 0");
        ASSERT(bb_merge_masks(&bb_out, masks, 2) == 0, "merge masks pass");
        ASSERT(bb_out == bb, "merge masks result");

        return any_test_failed();
}
