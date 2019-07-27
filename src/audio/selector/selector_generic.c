// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2019 Intel Corporation. All rights reserved.
//
// Author: Lech Betlej <lech.betlej@linux.intel.com>

/**
 * \file audio/selector_generic.c
 * \brief Audio channel selector / extractor - generic processing functions
 * \authors Lech Betlej <lech.betlej@linux.intel.com>
 */

#include <sof/audio/selector.h>

/**
 * \brief Channel selection for 16 bit, 1 channel data format.
 * \param[in,out] dev Selector base component device.
 * \param[in,out] sink Destination buffer.
 * \param[in,out] source Source buffer.
 * \param[in] frames Number of frames to process.
 */
static void sel_s16le_1ch(struct comp_dev *dev, struct comp_buffer *sink,
			  struct comp_buffer *source, uint32_t frames)
{
	struct comp_data *cd = comp_get_drvdata(dev);
	int16_t *src;
	int16_t *dest;
	uint32_t i;
	uint32_t j = 0;
	uint32_t nch = cd->config.in_channels_count;

	for (i = cd->config.sel_channel; i < frames * nch; i += nch) {
		src = buffer_read_frag_s16(source, i);
		dest = buffer_write_frag_s16(sink, j++);
		*dest = *src;
	}
}

/**
 * \brief Channel selection for 32 bit, 1 channel data format.
 * \param[in,out] dev Selector base component device.
 * \param[in,out] sink Destination buffer.
 * \param[in,out] source Source buffer.
 * \param[in] frames Number of frames to process.
 */
static void sel_s32le_1ch(struct comp_dev *dev, struct comp_buffer *sink,
			  struct comp_buffer *source, uint32_t frames)
{
	struct comp_data *cd = comp_get_drvdata(dev);
	int32_t *src;
	int32_t *dest;
	uint32_t i;
	uint32_t j = 0;
	uint32_t nch = cd->config.in_channels_count;

	for (i = cd->config.sel_channel; i < frames * nch; i += nch) {
		src = buffer_read_frag_s32(source, i);
		dest = buffer_write_frag_s32(sink, j++);
		*dest = *src;
	}
}

/**
 * \brief Channel selection for 16 bit, at least 2 channels data format.
 * \param[in,out] dev Selector base component device.
 * \param[in,out] sink Destination buffer.
 * \param[in,out] source Source buffer.
 * \param[in] frames Number of frames to process.
 */
static void sel_s16le_nch(struct comp_dev *dev, struct comp_buffer *sink,
			  struct comp_buffer *source, uint32_t frames)
{
	struct comp_data *cd = comp_get_drvdata(dev);
	int16_t *src;
	int16_t *dest;
	uint32_t i;
	uint32_t j = 0;
	uint32_t channel;

	for (i = 0; i < frames; i++) {
		for (channel = 0; channel < cd->config.in_channels_count;
		     channel++) {
			src = buffer_read_frag_s16(source, j);
			dest = buffer_write_frag_s16(sink, j);
			*dest = *src;
			j++;
		}
	}
}

/**
 * \brief Channel selection for 32 bit, at least 2 channels data format.
 * \param[in,out] dev Selector base component device.
 * \param[in,out] sink Destination buffer.
 * \param[in,out] source Source buffer.
 * \param[in] frames Number of frames to process.
 */
static void sel_s32le_nch(struct comp_dev *dev, struct comp_buffer *sink,
			  struct comp_buffer *source, uint32_t frames)
{
	struct comp_data *cd = comp_get_drvdata(dev);
	int32_t *src;
	int32_t *dest;
	uint32_t i;
	uint32_t j = 0;
	uint32_t channel;

	for (i = 0; i < frames; i++) {
		for (channel = 0; channel < cd->config.in_channels_count;
		     channel++) {
			src = buffer_read_frag_s32(source, j);
			dest = buffer_write_frag_s32(sink, j);
			*dest = *src;
			j++;
		}
	}
}

const struct comp_func_map func_table[] = {
	{SOF_IPC_FRAME_S16_LE, 1, sel_s16le_1ch},
	{SOF_IPC_FRAME_S24_4LE, 1, sel_s32le_1ch},
	{SOF_IPC_FRAME_S32_LE, 1, sel_s32le_1ch},
	{SOF_IPC_FRAME_S16_LE, 2, sel_s16le_nch},
	{SOF_IPC_FRAME_S24_4LE, 2, sel_s32le_nch},
	{SOF_IPC_FRAME_S32_LE, 2, sel_s32le_nch},
	{SOF_IPC_FRAME_S16_LE, 4, sel_s16le_nch},
	{SOF_IPC_FRAME_S24_4LE, 4, sel_s32le_nch},
	{SOF_IPC_FRAME_S32_LE, 4, sel_s32le_nch},
};

sel_func sel_get_processing_function(struct comp_dev *dev)
{
	struct comp_data *cd = comp_get_drvdata(dev);
	int i;
	/* map the channel selection function for source and sink buffers */
	for (i = 0; i < ARRAY_SIZE(func_table); i++) {
		if (cd->source_format != func_table[i].source)
			continue;
		if (cd->config.out_channels_count != func_table[i].out_channels)
			continue;

		/* TODO: add additional criteria as needed */
		return func_table[i].sel_func;
	}

	return NULL;
}
