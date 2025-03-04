/* SPDX-License-Identifier: GPL-2.0+
 * Copyright (c) 2017-2020 Realtek Semiconductor Corp.
 */

#ifndef SND_REALTEK_H
#define SND_REALTEK_H

#include <sound/pcm.h>
#include <soc/realtek/uapi/ion_rtk.h>
#include "snd-realtek_common.h"

//////////////////
// Main Control //
//////////////////
#define CAPTURE_USE_PTS_RING

#define S_OK 0x10000000
#define CONVERT_FOR_AVCPU(x) (x)
#define AUDIO_ION_FLAG (ION_USAGE_MMAP_WRITECOMBINE | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC)

//////////////
// playback //
//////////////
#define RTK_DMP_PLAYBACK_INFO (SNDRV_PCM_INFO_INTERLEAVED | \
								SNDRV_PCM_INFO_NONINTERLEAVED | \
								SNDRV_PCM_INFO_RESUME | \
								SNDRV_PCM_INFO_MMAP | \
								SNDRV_PCM_INFO_MMAP_VALID | \
								SNDRV_PCM_INFO_NO_PERIOD_WAKEUP | \
								SNDRV_PCM_INFO_PAUSE)
#define RTK_DMP_PLAYBACK_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_3LE)
#define RTK_DMP_PLYABACK_RATES (SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 \
					 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 \
					 | SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000)
#define RTK_DMP_PLAYBACK_RATE_MIN       16000
#define RTK_DMP_PLAYBACK_RATE_MAX       192000
#define RTK_DMP_PLAYBACK_CHANNELS_MIN   1
#define RTK_DMP_PLAYBACK_CHANNELS_MAX   8
#define RTK_DMP_PLAYBACK_MAX_BUFFER_SIZE         (32*1024)//(16*1024)
#define RTK_DMP_PLAYBACK_MIN_PERIOD_SIZE         64
#define RTK_DMP_PLAYBACK_MAX_PERIOD_SIZE         (8*1024)
#define RTK_DMP_PLAYBACK_PERIODS_MIN             4
#define RTK_DMP_PLAYBACK_PERIODS_MAX             1024
#define RTK_DMP_PLAYBACK_FIFO_SIZE               32

/////////////
// capture //
/////////////
#define RTK_DMP_CAPTURE_INFO RTK_DMP_PLAYBACK_INFO
#define RTK_DMP_CAPTURE_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)
#define RTK_DMP_CAPTURE_RATES (SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#define RTK_DMP_CAPTURE_RATE_MIN 16000
#define RTK_DMP_CAPTURE_RATE_MAX 48000
#define RTK_DMP_CAPTURE_CHANNELS_MIN 2
#define RTK_DMP_CAPTURE_CHANNELS_MAX 2
#define RTK_DMP_CAPTURE_MAX_BUFFER_SIZE         RTK_DMP_PLAYBACK_MAX_BUFFER_SIZE
#define RTK_DMP_CAPTURE_MIN_PERIOD_SIZE         RTK_DMP_PLAYBACK_MIN_PERIOD_SIZE
#define RTK_DMP_CAPTURE_MAX_PERIOD_SIZE         16*1024
#define RTK_DMP_CAPTURE_PERIODS_MIN             RTK_DMP_PLAYBACK_PERIODS_MIN
#define RTK_DMP_CAPTURE_PERIODS_MAX             RTK_DMP_PLAYBACK_PERIODS_MAX
#define RTK_DMP_CAPTURE_FIFO_SIZE               RTK_DMP_PLAYBACK_FIFO_SIZE

#define RTK_DEC_AO_BUFFER_SIZE          (7*1024)//(10*1024)
#define RTK_ENC_AI_BUFFER_SIZE          (32*1024)//(64*1024)
#define RTK_ENC_LPCM_BUFFER_SIZE        (32*1024)
#define RTK_ENC_PTS_BUFFER_SIZE         (8*1024)

enum{
	ENUM_AIN_HDMIRX = 0,
	ENUM_AIN_I2S,  // from ADC outside of IC
	ENUM_AIN_AUDIO,
	ENUM_AIN_AUDIO_V2,
	ENUM_AIN_AUDIO_V3,
	ENUM_AIN_AUDIO_V4,
	ENUM_AIN_I2S_LOOPBACK,
	ENUM_AIN_DMIC_PASSTHROUGH,
	ENUM_AIN_PURE_DMIC
};

////////////////////////////////////////////
////////////////////////////////////////////

#define MAX_PCM_DEVICES     1 //2 todo
#define MAX_PCM_SUBSTREAMS  3
#define MAX_AI_DEVICES      2

#define MIXER_ADDR_MASTER   0
#define MIXER_ADDR_LINE     1
#define MIXER_ADDR_MIC      2
#define MIXER_ADDR_SYNTH    3
#define MIXER_ADDR_CD       4
#define MIXER_ADDR_LAST     4

#define MARS_VOLUME(xname, xindex, addr)    \
{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
	.info = snd_RTK_volume_info,\
	.get = snd_RTK_volume_get, .put = snd_RTK_volume_put,\
	.private_value = addr }

#define MARS_CAPSRC(xname, xindex, addr)    \
{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
	.info = snd_RTK_capsrc_info,\
	.get = snd_RTK_capsrc_get, .put = snd_RTK_capsrc_put,\
	.private_value = addr }

#define RING32_2_RING64(pRing64, pRing32) \
{\
	pRing64->base = (unsigned long)pRing32->base; \
	pRing64->limit = (unsigned long)pRing32->limit; \
	pRing64->wp = (unsigned long)pRing32->wp; \
	pRing64->rp = (unsigned long)pRing32->rp; \
	pRing64->cp = (unsigned long)pRing32->cp; \
}

/************************************************************************/
/* ENUM                                                                 */
/************************************************************************/
enum AVSYNC_MODE {
	AVSYNC_FORCED_SLAVE,
	AVSYNC_FORCED_MASTER,
	AVSYNC_AUTO_SLAVE,
	AVSYNC_AUTO_MASTER,
	AVSYNC_AUTO_MASTER_NO_SKIP,
	AVSYNC_AUTO_MASTER_CONSTANT_DELAY   /* after getback mastership, it become force master */
};

struct MASTERSHIP {
	unsigned char systemMode;  /* enum AVSYNC_MODE */
	unsigned char videoMode;   /* enum AVSYNC_MODE */
	unsigned char audioMode;   /* enum AVSYNC_MODE */
	unsigned char masterState; /* enum AUTOMASTER_STATE */
};

/* change this structure, make sure to change the CReferenceClock definition*/
struct REFCLOCK {
	long long      RCD;
	unsigned int  RCD_ext;
	long long      GPTSTimeout;
	long long      videoSystemPTS;
	long long      audioSystemPTS;
	long long      videoRPTS;
	long long      audioRPTS;
	unsigned int  videoContext;
	unsigned int  audioContext;

	struct MASTERSHIP     mastership;
	unsigned int  videoFreeRunThreshold;
	unsigned int  audioFreeRunThreshold;
	long long      masterGPTS;   // this is the value of GPTS (hardware PTS) when master set the reference clock
	int           audioFullness;   // This flag will be turned on when AE's output buffer is almost full.
	// VE which is monitoring this flag will issue auto-pause then.
	// (0: still have enough output space for encoding.   1: AE request pause)
	int           audioPauseFlag;  // This flag will be turned on when VE decides to auto-pause.
	// AE which is monitoring this flag will auto-pause itself then.
	// (0: ignore.  1: AE have to pauseEncode immediately)

	int           VO_Underflow; // (0: VO is working properly; otherwise, VO underflow)
	int           AO_Underflow; // (0: AO is working properly; otherwise, AO underflow)
	int           videoEndOfSegment; // set to the flow EOS.eventID by VO after presenting the EOS sample
	int           audioEndOfSegment; // set to the flow EOS.eventID by AO after presenting the EOS sample
	unsigned char  reserved[16];
};

enum AUDIO_PATH_T {
	AUDIO_PATH_NO_DEFINE = 0,
	AUDIO_PATH_DECODER_AO,
	AUDIO_PATH_AO_BYPASS
};

enum SND_REALTEK_EOS_STATE_T {
	SND_REALTEK_EOS_STATE_NONE = 0,
	SND_REALTEK_EOS_STATE_PROCESSING,
	SND_REALTEK_EOS_STATE_FINISH
};

enum RINGBUFFER_TYPE {
	RINGBUFFER_STREAM,
	RINGBUFFER_COMMAND,
	RINGBUFFER_MESSAGE,
	RINGBUFFER_VBI,
	RINGBUFFER_PTS,
	RINGBUFFER_DTVCC
};

enum OMX_AUDIO_VERSION {
	ENUM_OMX_AUDIO_VERSION_0 = 0,
	ENUM_OMX_AUDIO_VERSION_1 = 1,
};

enum AUDIO_CONFIG_CMD_MSG {
	AUDIO_CONFIG_CMD_SPEAKER = 0,
	AUDIO_CONFIG_CMD_AGC = 1,
	AUDIO_CONFIG_CMD_SPDIF = 2,
	AUDIO_CONFIG_CMD_VOLUME = 3,
	AUDIO_CONFIG_CMD_MUTE = 4,
	AUDIO_CONFIG_CMD_AO_MIC = 5,
	AUDIO_CONFIG_CMD_AO_AUX = 6,
	AUDIO_CONFIG_CMD_AO_ECHO_REVERB = 7,
	AUDIO_CONFIG_CMD_AO_MIC1_VOLUME = 8,
	AUDIO_CONFIG_CMD_AO_MIC2_VOLUME = 9,
	AUDIO_CONFIG_CMD_AO_DEC_VOLUME = 10,
	AUDIO_CONFIG_CMD_AO_AUX_VOLUME = 11,
	AUDIO_CONFIG_CMD_DAC_SWITCH = 12,
	AUDIO_CONFIG_CMD_DD_DUALMONO = 13,
	AUDIO_CONFIG_CMD_DD_SCALE = 14,
	AUDIO_CONFIG_CMD_DD_DOWNMIXMODE = 15,
	AUDIO_CONFIG_CMD_DD_COMP = 16,
	AUDIO_CONFIG_CMD_DD_LFE = 17,
	AUDIO_CONFIG_CMD_DD_STEREOMIX = 18,
	AUDIO_CONFIG_CMD_DIGITAL_OUT = 19,
	AUDIO_CONFIG_CMD_EXCLUSIVE = 20,
	AUDIO_CONFIG_CMD_AC3_SPDIF_RAW = 21,
	AUDIO_CONFIG_CMD_AC3_HDMI_RAW = 22,
	AUDIO_CONFIG_CMD_DTS_SPDIF_RAW = 23,
	AUDIO_CONFIG_CMD_DTS_HDMI_RAW = 24,
	AUDIO_CONFIG_CMD_MPG_SPDIF_RAW = 25,
	AUDIO_CONFIG_CMD_MPG_HDMI_RAW = 26,
	AUDIO_CONFIG_CMD_AAC_SPDIF_RAW = 27,
	AUDIO_CONFIG_CMD_AAC_HDMI_RAW = 28,
	AUDIO_CONFIG_CMD_MLP_HDMI_RAW = 29,
	AUDIO_CONFIG_CMD_DDP_HDMI_RAW = 30,
	AUDIO_CONFIG_CMD_HDMI_CHANNEL_OUT = 31,
	AUDIO_CONFIG_CMD_FORCE_CHANNEL_CODEC = 32,
	AUDIO_CONFIG_CMD_MLP_SPDIF_RAW = 33,
	AUDIO_CONFIG_CMD_DDP_SPDIF_RAW = 34,
	AUDIO_CONFIG_CMD_MAX_OUTPUT_SAMPLERATE = 35,
	AUDIO_CONFIG_CMD_USB_DEVICE_SUPPORT_SAMPLERATE = 36,
	AUDIO_CONFIG_CMD_KARAOKE_MODE = 37,
	AUDIO_CONFIG_CMD_BRAZIL_LATM_AAC = 38,
	AUDIO_CONFIG_CMD_DRC_PERCENT = 39,
	AUDIO_CONFIG_CMD_LICENSE_MODE = 40,
	AUDIO_CONFIG_CMD_AUDIO_TYPE_PRIORITY = 41,
	AUDIO_CONFIG_CMD_SPDIF_OUTPUT_SWITCH = 42,
	AUDIO_CONFIG_CMD_CUSTOMIZE_REQUEST = 43,
	AUDIO_CONFIG_CMD_DEC_PLAYBACK_RATE = 44,
	AUDIO_CONFIG_CMD_SAMPLERATE_TOLERANCE = 45,
	AUDIO_CONFIG_CMD_KARAOKE_GENDER_CHANGE = 46,
	AUDIO_CONFIG_CMD_DAC_OUTPUT_SWITCH = 47,
	AUDIO_CONFIG_CMD_SET_DEC_DELAY_RP = 48,
	AUDIO_CONFIG_CMD_MPEG2_AAC_LOW_SR_SPDIF_RAW = 49,
	AUDIO_CONFIG_CMD_MPEG2_AAC_LOW_SR_HDMI_RAW = 50,
	AUDIO_CONFIG_CMD_MPEG4_AAC_SPDIF_RAW = 51,
	AUDIO_CONFIG_CMD_MPEG4_AAC_HDMI_RAW = 52,
	AUDIO_CONFIG_CMD_HDMI_OUTPUT_SWITCH = 53,
	AUDIO_CONFIG_CMD_SPDIF_SCMS = 54,
	AUDIO_CONFIG_CMD_DAC_ANALOG_GAIN = 55,
	AUDIO_CONFIG_CMD_POWER_SAVING_SETUP = 56,
	AUDIO_CONFIG_TRUEHD_ERR_SELF_RESET_ENABLED = 57,
};

enum ENUM_AUDIO_HDMI_EDID_ENABLE {
	ENUM_AUDIO_EDID_DISABLE = 0,
	ENUM_AUDIO_EDID_ENABLE = 1,
	ENUM_AUDIO_EDID_START = 2,
	ENUM_AUDIO_EDID_END = 3,
};

//  downmix could be placed on in-band queue
//  set media type or private information to in-band queue
enum AUDIO_INBAND_CMD_TYPE {
	/* Audio Decoder In-band Command */
	AUDIO_DEC_INBAND_CMD_TYPE_PTS = 0,
	AUDIO_DEC_INBAND_CMD_TYPE_NEW_SEG = 1,      /* let begin_AGC_gain = 1 */
	AUDIO_DEC_INBAMD_CMD_TYPE_NEW_FORMAT = 2,
	AUDIO_DEC_INBAND_CMD_TYPE_EOS = 3,          /* Can not be passed, sent back to system */
	AUDIO_DEC_INBAND_CMD_TYPE_CONTEXT = 4,      /* write debug information, need a RPC_ToSystem command *//* Can not be passed, sent back to system */
	AUDIO_DEC_INBAND_CMD_TYPE_DECODE = 5,       /* Information for each decoder is inclueded */
	AUDIO_DEC_INABND_CMD_TYPE_PTS_SKIP = 6,
	AUDIO_DEC_INBAND_CMD_TYPE_PRIVATE_INFO = 7,
	AUDIO_DEC_INBAND_CMD_TYPE_VORBIS_PACKETINFO = 8,    /* Information about vorbis packets */

	AUDIO_DEC_INBAND_CMD_TYPE_BS_DISCONTINUITY = 9,
	AUDIO_DEC_INBAND_CMD_TYPE_RESYNC = 10,
	AUDIO_DEC_INBAND_CMD_TYPE_CGMS_INFO = 11,
	AUDIO_DEC_INBAND_CMD_TYPE_RALSD_INFO = 12,
	AUDIO_DEC_INBAND_CMD_TYPE_WMAPRO_DRC = 13,
	AUDIO_DEC_INBAND_CMD_TYPE_WMAPRO_DWNMIX_MTRX = 14,

	AUDIO_DEC_INBAND_CMD_TYPE_EMPHASIS = 15,        // for lpcm emphasis info

	/* Audio AO Mixer In-band Command */
	AUDIO_AO_MIXER_INBAND_CMD_TYPE_SET_MIXER_RPTS = 64,
	AUDIO_AO_MIXER_INBAND_CMD_TYPE_SET_BLEND,

	/* Audio DV Mixer In-band Command */
	AUDIO_DV_MIXER_INBAND_CMD_TYPE_SET_BLEND
};

enum AUDIO_DEC_TYPE {
	AUDIO_UNKNOWN_TYPE = 0,
	AUDIO_MPEG_DECODER_TYPE = 1,
	AUDIO_AC3_DECODER_TYPE = 2,
	AUDIO_LPCM_DECODER_TYPE = 3,
	AUDIO_DTS_DECODER_TYPE = 4,
	AUDIO_WMA_DECODER_TYPE = 5,
	AUDIO_AAC_DECODER_TYPE = 6,
	AUDIO_VORBIS_DECODER_TYPE = 7,
	AUDIO_DV_DECODER_TYPE = 8,
	AUDIO_MLP_DECODER_TYPE = 9,
	AUDIO_DDP_DECODER_TYPE = 10,
	AUDIO_DTS_HD_DECODER_TYPE = 11,
	AUDIO_WMA_PRO_DECODER_TYPE = 12,
	AUDIO_MP4AAC_DECODER_TYPE = 13,
	AUDIO_MP3_PRO_DECODER_TYPE = 14,
	AUDIO_MP4HEAAC_DECODER_TYPE = 15,
	AUDIO_RAW_AAC_DECODER_TYPE = 16,
	AUDIO_RA1_DECODER_TYPE = 17,
	AUDIO_RA2_DECODER_TYPE = 18,
	AUDIO_ATRAC3_DECODER_TYPE = 19,
	AUDIO_COOK_DECODER_TYPE = 20,
	AUDIO_LSD_DECODER_TYPE = 21,
	AUDIO_ADPCM_DECODER_TYPE = 22,
	AUDIO_FLAC_DECODER_TYPE = 23,
	AUDIO_ULAW_DECODER_TYPE = 24,
	AUDIO_ALAW_DECODER_TYPE = 25,
	AUDIO_ALAC_DECODER_TYPE = 26,
	AUDIO_DTS_HIGH_RESOLUTION_DECODER_TYPE = 27,
	AUDIO_DTS_LBR_DECODER_TYPE = 28,
	AUDIO_DTS_MASTER_AUDIO_DECODER_TYPE = 29,
	AUDIO_AMR_DECODER_TYPE = 30,
	AUDIO_MIDI_DECODER_TYPE = 31,
	AUDIO_APE_DECODER_TYPE = 32,
	AUDIO_AVS_DECODER_TYPE = 33,
	AUDIO_NELLYMOSER_DECODER_TYPE = 34,
	AUDIO_WMA_LOSSLESS_DECODER_TYPE = 35,
	AUDIO_UNCERTAIN_DECODER_TYPE = 36,
	AUDIO_UNCERTAIN_HDMV_DECODER_TYPE = 37,
	AUDIO_ILBC_DECODER_TYPE = 38,
};

enum AUDIO_MODULE_TYPE {
	AUDIO_OUT = 7,
	AUDIO_IN = 8,
	AUDIO_ENCODER = 9,
	AUDIO_MPEG_ENCODER = 10,
	AUDIO_ALSA_OUT = 12,
	AUDIO_PSEUDO_OUT = 14,
	AUDIO_PP_OUT = 15,
	AUDIO_DECODER = 16,
	AUDIO_UNKNOWN = 17,
	AUDIO_LPCM_ENCODER = 19,
	AUDIO_AAC_ENCODER = 21,
	AUDIO_MP3_ENCODER = 22,
	AUDIO_RV_PARSER = 23,
	AUDIO_AC3_ENCODER = 24,
	AUDIO_VIENNA_OUT = 25,
	AUDIO_DTS_ENCODER = 26,
};

enum AUDIO_ENUM_PRIVAETINFO {
	ENUM_PRIVATEINFO_AUDIO_FORMAT_PARSER_CAPABILITY = 0,
	ENUM_PRIVATEINFO_AUDIO_DECODER_CAPABILITY = 1,
	ENUM_PRIVATEINFO_AUDIO_CONFIG_CMD_BS_INFO = 2,
	ENUM_PRIVATEINFO_AUDIO_CHECK_LPCM_ENDIANESS = 3,
	ENUM_PRIVATEINFO_AUDIO_CONFIG_CMD_AO_DELAY_INFO = 4,
	ENUM_PRIVATEINFO_AUDIO_AO_CHANNEL_VOLUME_LEVEL = 5,
	ENUM_PRIVATEINFO_AUDIO_GET_FLASH_PIN = 6,
	ENUM_PRIVATEINFO_AUDIO_RELEASE_FLASH_PIN = 7,
	ENUM_PRIVATEINFO_AUDIO_GET_MUTE_N_VOLUME = 8,
	ENUM_PRIVATEINFO_AUDIO_AO_MONITOR_FULLNESS = 9,
	ENUM_PRIVATEINFO_AUDIO_CONTROL_FLASH_VOLUME = 10,
	ENUM_PRIVATEINFO_AUDIO_CONTROL_DAC_SWITCH = 11,
	ENUM_PRIVATEINFO_AUDIO_PREPROCESS_CONFIG = 12,
	ENUM_PRIVATEINFO_AUDIO_CHECK_SECURITY_ID = 13,
	ENUM_PRIVATEINFO_AUDIO_LOW_DELAY_PARAMETERS = 14,
	ENUM_PRIVATEINFO_AUDIO_SET_NETWORK_JITTER = 15,
	ENUM_PRIVATEINFO_AUDIO_GET_QUEUE_DATA_SIZE = 16,
	ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA = 17,
	ENUM_PRIVATEINFO_AUDIO_AI_CONNECT_ALSA = 18,
	ENUM_PRIVATEINFO_AUDIO_SET_PCM_FORMAT = 19,
	ENUM_PRIVATEINFO_AUDIO_DO_SELF_DESTROY_FLOW = 20,
	ENUM_PRIVATEINFO_AUDIO_GET_SAMPLING_RATE = 21,
	ENUM_PRIVATEINFO_AUDIO_SLAVE_TIMEOUT_THRESHOLD = 22,
	ENUM_PRIVATEINFO_AUDIO_GET_GLOBAL_AO_INSTANCEID = 23,
	ENUM_PRIVATEINFO_AUDIO_SET_CEC_PARAMETERS = 24,
	ENUM_PRIVATEINFO_AUDIO_INIT_DBG_DUMP_MEM = 25,
	ENUM_PRIVATEINFO_AUDIO_AI_GET_AO_FLASH_PIN = 26,
	ENUM_PRIVATEINFO_AUDIO_AI_SET_AO_FLASH_PIN = 27,
	ENUM_PRIVATEINFO_AUDIO_GET_PP_FREE_PINID = 28,
	ENUM_PRIVATEINFO_AUDIO_HDMI_RX_CONNECT_TO_BT = 29,
	ENUM_PRIVATEINFO_AUDIO_GET_BS_ERR_RATE = 30,
	ENUM_PRIVATEINFO_AUDIO_SET_RESUME_IR_KEYS = 31,
	ENUM_PRIVATEINFO_SET_GSTREAMER_PTS_ACC_MODE = 32,
	ENUM_PRIVATEINFO_AUDIO_GET_BONDING_TYPE = 33,
	ENUM_PRIVATEINFO_AUDIO_SHARE_MEMORY_FOR_PORTING_FIRMWARE = 34,
	ENUM_PRIVATEINFO_AUDIO_SET_DVDPLAYER_AO_VERSION = 35,
	ENUM_PRIVATEINFO_AUDIO_MS_PP_CERT = 36,
	ENUM_PRIVATEINFO_AUDIO_TRIGGER_EVENT = 37,
	ENUM_PRIVATEINFO_AUDIO_AI_NON_PCM_IN = 38,
	ENUM_PRIVATEINFO_OMX_AUDIO_VERSION = 39,
	ENUM_PRIVATEINFO_AUDIO_AI_PAD_IN = 40,
	ENUM_PRIVATEINFO_AUDIO_MS_MAJOR_DECODER_PIN = 41,
	ENUM_PRIVATEINFO_AUDIO_PROVIDE_RAWOUT_LATENCY = 42,
	ENUM_PRIVATEINFO_AUDIO_MS_MIXER_IGNORE_PIN = 43,
	ENUM_PRIVATEINFO_AUDIO_MS_CERTIFICATION_PLATFORM = 44,
	ENUM_PRIVATEINFO_AUDIO_MS_MIXER_PIN_NEW_SEG = 45,
	ENUM_PRIVATEINFO_AUDIO_MS_DEC_DROP_BY_PTS = 46,
	ENUM_PRIVATEINFO_AUDIO_MS_DEC_INIT_PTS_OFFSET = 47,
	ENUM_PRIVATEINFO_AUDIO_MS_PP_OUTPUT_TYPE = 48,
	ENUM_PRIVATEINFO_AUDIO_DTS_ENCODER_CONFIG = 49,
	ENUM_PRIVATEINFO_AUDIO_GET_FW_VERSION = 50,
	ENUM_PRIVATEINFO_AUDIO_DTS_M8_IN_CONFIG = 51,
	ENUM_PRIVATEINFO_AUDIO_DTS_M8_LA_NUM = 52,
	ENUM_PRIVATEINFO_AUDIO_DTS_M8_SET_OUTPUT_FORMAT = 53,
	ENUM_PRIVATEINFO_AUDIO_SET_DRC_CFG = 54,
	ENUM_PRIVATEINFO_AUDIO_DTS_M8_LA_ERROR_MSG = 55,
	ENUM_PRIVATEINFO_GET_B_VALUE = 56,
	ENUM_PRIVATEINFO_AUDIO_ENTER_SUSPEND = 57,
	ENUM_PRIVATEINFO_AUDIO_MPEGH_IN_CONFIG = 58,
	ENUM_PRIVATEINFO_AUDIO_SET_LOW_WATERLEVEL = 59,
};

enum AUDIO_CHANNEL_OUT_INDEX {
	AUDIO_NULL_CHANNEL_INDEX = 0,
	AUDIO_LEFT_FRONT_INDEX = 1,
	AUDIO_RIGHT_FRONT_INDEX = 2,
	AUDIO_CENTER_FRONT_INDEX = 5,
	AUDIO_LFE_INDEX = 6,
	AUDIO_LEFT_SURROUND_REAR_INDEX = 3,
	AUDIO_RIGHT_SURROUND_REAR_INDEX = 4,
	AUDIO_LEFT_OUTSIDE_FRONT_INDEX = 7,
	AUDIO_RIGHT_OUTSIDE_FRONT_INDEX = 8,
	AUDIO_SPDIF_LEFT_CHANNEL_INDEX = 9,
	AUDIO_SPDIF_RIGHT_CHANNEL_INDEX = 10,
	AUDIO_SURROUND_INDEX = 11,
	AUDIO_CENTER_SURROUND_REAR_INDEX = 12,
	AUDIO_OverHead_INDEX = 13,
	AUDIO_LEFT_SURROUND_INDEX = 14,
	AUDIO_RIGHT_SURROUND_INDEX = 15,
	AUDIO_LEFT_FRONT_HIGH_INDEX = 16,
	AUDIO_RIGHT_FRONT_HIGH_INDEX = 17,
	AUDIO_LEFT_INNER_FRONT_INDEX = 18,
	AUDIO_RIGHT_INNER_FRONT_INDEX = 19,
	AUDIO_LEFT_REAR_INDEX = 20,
	AUDIO_RIGHT_REAR_INDEX = 21,
	AUDIO_LEFT_SURROUND_DIRECT_INDEX = 22,
	AUDIO_RIGHT_SURROUND_DIRECT_INDEX = 23,
	AUDIO_CENTER_FRONT_HIGH_INDEX = 24,
	AUDIO_LFE2_INDEX = 25,
	AUDIO_SPDIF_NON_PCM_TYPE = 256,
	AUDIO_ENABLE_DOWNMIX = 257,
};

enum AUDIO_FORMAT_OF_AI_SEND_TO_ALSA {
	AUDIO_ALSA_FORMAT_32BITS_BE_PCM = 0,
	AUDIO_ALSA_FORMAT_16BITS_LE_LPCM = 1,
	AUDIO_ALSA_FORMAT_24BITS_LE_LPCM = 2,
	AUDIO_ALSA_FORMAT_NONE = 3,
	AUDIO_ALSA_FORMAT_TOTAL_NUM = 3 + 1,
};

enum AUDIO_ENDIANTYPE {
	AUDIO_BIG_ENDIAN        = 0,       // CD,DVD type
	AUDIO_LITTLE_ENDIAN     = 1,
	AUDIO_LPCM_DHMV_TYPE    = 2,       // HDMV type
};

enum AUDIO_SAMPLERATE {
	AUDIO_SAMPLERATE_32000 = 0x1,
	AUDIO_SAMPLERATE_44100 = 0x2,
	AUDIO_SAMPLERATE_48000 = 0x4,
	AUDIO_SAMPLERATE_88200 = 0x8,
	AUDIO_SAMPLERATE_96000 = 0x10,
	AUDIO_SAMPLERATE_176400 = 0x20,
	AUDIO_SAMPLERATE_192000 = 0x40,
	AUDIO_SAMPLERATE_22050 = 0x80,
	AUDIO_SAMPLERATE_24000 = 0x100,
	AUDIO_SAMPLERATE_64000 = 0x200,
	AUDIO_SAMPLERATE_16000 = 0x400,
	AUDIO_SAMPLERATE_8000 = 0x800,
	AUDIO_SAMPLERATE_11025 = 0x1000,
};

enum USB_AUDIO_IN_CMD {
	ENUM_USB_AUDIO_IN_CMD_DISCONNECT = 0,
	ENUM_USB_AUDIO_IN_CMD_CONNECT = 1,
	ENUM_USB_AUDIO_IN_CMD_STOP = 2,
	ENUM_USB_AUDIO_IN_CMD_START = 3,
	ENUM_USB_AUDIO_IN_CMD_GETINFO = 4,
	ENUM_USB_AUDIO_IN_CMD_SETINFO = 5,
};

enum ALSA_WRITE_STATE {
	ENUM_START_STATE = 1,
	ENUM_SLEEP_STATE,
	ENUM_IN_COPY_LOOP_STATE,
	ENUM_IN_WAIT_LOOP_STATE,
	ENUM_END_STATE
};

enum USB_AUDIO_IN_FORMAT {
	ENUM_USB_AUDIO_IN_FORMAT_SIGNED_8BITS = 0x1,
	ENUM_USB_AUDIO_IN_FORMAT_SIGNED_16BITS = 0x2,
	ENUM_USB_AUDIO_IN_FORMAT_SIGNED_24BITS = 0x4,
	ENUM_USB_AUDIO_IN_FORMAT_SIGNED_32BITS = 0x8,
	ENUM_USB_AUDIO_IN_FORMAT_UNSIGNED_8BITS = 0x10,
	ENUM_USB_AUDIO_IN_FORMAT_UNSIGNED_16BITS = 0x20,
	ENUM_USB_AUDIO_IN_FORMAT_UNSIGNED_24BITS = 0x40,
	ENUM_USB_AUDIO_IN_FORMAT_UNSIGNED_32BITS = 0x80,
};

enum AO_FLASH_PCM_FORMAT {
	ENUM_AO_FLASH_32BIT_BE = 0,
	ENUM_AO_FLASH_24BIT_BE,
	ENUM_AO_FLASH_16BIT_BE,
	ENUM_AO_FLASH_24BIT_LE,
	ENUM_AO_FLASH_16BIT_LE,
	ENUM_AO_FLASH_8BIT
};

enum ENUM_AUDIO_CHANNEL_OUT_INDEX {
	ENUM_AUDIO_NULL_CHANNEL_INDEX = 0,

	ENUM_AUDIO_LEFT_FRONT_INDEX = 1,            // L
	ENUM_AUDIO_RIGHT_FRONT_INDEX = 2,           // R
	ENUM_AUDIO_CENTER_FRONT_INDEX = 5,          // C
	ENUM_AUDIO_LFE_INDEX = 6,                   // LFE
	ENUM_AUDIO_LEFT_SURROUND_REAR_INDEX = 3,    // Ls or Lsr
	ENUM_AUDIO_RIGHT_SURROUND_REAR_INDEX = 4,   // Rs or Rsr
	ENUM_AUDIO_LEFT_OUTSIDE_FRONT_INDEX = 7,    // ENUM_AUDIO_LEFT_SURROUND_SIDE_INDEX,  Lss
	ENUM_AUDIO_RIGHT_OUTSIDE_FRONT_INDEX = 8,   // ENUM_AUDIO_RIGHT_SURROUND_SIDE_INDEX, Rss
	ENUM_AUDIO_SPDIF_LEFT_CHANNEL_INDEX = 9,
	ENUM_AUDIO_SPDIF_RIGHT_CHANNEL_INDEX = 10,

	ENUM_AUDIO_SURROUND_INDEX = 11,
	ENUM_AUDIO_CENTER_SURROUND_REAR_INDEX = 12,
	ENUM_AUDIO_OverHead_INDEX = 13,

	ENUM_AUDIO_LEFT_SURROUND_INDEX = 14,
	ENUM_AUDIO_RIGHT_SURROUND_INDEX = 15,
	ENUM_AUDIO_LEFT_FRONT_HIGH_INDEX = 16,
	ENUM_AUDIO_RIGHT_FRONT_HIGH_INDEX = 17,
	ENUM_AUDIO_LEFT_INNER_FRONT_INDEX = 18,
	ENUM_AUDIO_RIGHT_INNER_FRONT_INDEX = 19,
	ENUM_AUDIO_LEFT_REAR_INDEX = 20,
	ENUM_AUDIO_RIGHT_REAR_INDEX = 21,
	ENUM_AUDIO_LEFT_SURROUND_DIRECT_INDEX = 22,
	ENUM_AUDIO_RIGHT_SURROUND_DIRECT_INDEX = 23,
	ENUM_AUDIO_CENTER_FRONT_HIGH_INDEX = 24,
	ENUM_AUDIO_LFE2_INDEX = 25,

	ENUM_AUDIO_SPDIF_NON_PCM_TYPE = 256,
	ENUM_AUDIO_ENABLE_DOWNMIX = 257
};

enum ENUM_AUDIO_CHANNEL_IN {
	IN_NULL_CHANNEL = 0,
	ADC0_LEFT_CHANNEL_EN = 1,
	ADC0_RIGHT_CHANNEL_EN = 2,
	ADC1_LEFT_CHANNEL_EN = 4,
	ADC1_Right_CHANNEL_EN = 8,
	SPDIF_LEFT_CHANNEL_EN = 16,
	SPDIF_RIGHT_CHANNEL_EN = 32,
	ADC2_LEFT_CHANNEL_EN = 64,
	ADC2_RIGHT_CHANNEL_EN = 128,
};

enum ENUM_AUDIO_CHANNEL_OUT {
	OUT_NULL_CHANNEL = 0,
	LEFT_CENTER_FRONT_CHANNEL_EN = 1,
	RIGHT_CENTER_FRONT_CHANNEL_EN = 2,
	CENTER_FRONT_CHANNEL_EN = 4,
	LFE_CHANNEL_EN = 8,
	LEFT_SURROUND_CHANNEL_EN = 16,
	RIGHT_SURROUND_CHANNEL_EN = 32,
	LEFT_OUTSIDE_FRONT_CHANNEL_EN = 64,
	RIGHT_OUTSIDE_FRONT_CHANNEL_EN = 128,
	NON_PCM_OUT_EN = 256,
	ENABLE_DOWNMIX = 257,
};

enum AUDIO_ENUM_AIO_PRIVAETINFO {
	ENUM_PRIVATEINFO_AIO_AO_INTERFACE_SWITCH_CONTROL = 0,
	ENUM_PRIVATEINFO_AIO_AI_INTERFACE_SWITCH_CONTROL = 1,
	ENUM_PRIVATEINFO_AIO_ALSA_DESTROY_AI_FLOW = 2,
	ENUM_PRIVATEINFO_AIO_AI_NONPCM_WRITE_BACK_BS = 3,
	ENUM_PRIVATEINFO_AIO_HDMIRX_LATENCY_MEM = 4,
	ENUM_PRIVATEINFO_AIO_AI_LOOPBACK_AO = 5,
	ENUM_PRIVATEINFO_AIO_AI_LOOPBACK_HDMITX = 6,
	ENUM_PRIVATEINFO_AIO_AI_LOOPBACK_DAC = 7,
	ENUM_PRIVATEINFO_AIO_AI_ADC_ANALOG = 8,
	ENUM_PRIVATEINFO_AIO_AI_MULTIPLE_ADC = 9,
	ENUM_PRIVATEINFO_AIO_AI_ADC_AMIC = 9 + 1,
	ENUM_PRIVATEINFO_AIO_KERNEL_RPC = 9 + 2,
	ENUM_PRIVATEINFO_AIO_SET_SE_CLK = 9 + 3,
	ENUM_PRIVATEINFO_AIO_AI_PRIVATEINFO = 9 + 4,
	ENUM_PRIVATEINFO_AIO_DELIVER_SCPU_FW_PID = 9 + 5,
	ENUM_PRIVATEINFO_AIO_GET_D_VISION_CAPABILITY = 9 + 6,
	ENUM_PRIVATEINFO_AIO_GET_AUDIO_PROCESSING_AI = 9 + 7,
	ENUM_PRIVATEINFO_AIO_AI_GET_HW_VALID = 9 + 8,
	ENUM_PRIVATEINFO_AIO_IS_EARC_C = 9 + 9,
	ENUM_PRIVATEINFO_AIO_AO_FLASH_LPCM = 9 + 10,
	ENUM_PRIVATEINFO_AIO_TOTAL_NUM = 9 + 11,
};

enum ENUM_AI_PRIVATE_TYPE {
	ENUM_AI_PRIVATE_MUTE = 0,
	ENUM_AI_PRIVATE_WRITE_BACK_SYSTEM,
	ENUM_AI_PRIVATE_HDMI_RX_TO_SET_AO_FLASH,
	ENUM_AI_PRIVATE_HDMI_RX_TO_GET_AO_FLASH,
	ENUM_AI_PRIVATE_HDMI_RX_CONNECT_TO_BT_INFO,
	ENUM_AI_PRIVATE_NON_PCM_IN,
	ENUM_AI_PRIVATE_SET_PAD_SOURCE,
	ENUM_AI_PRIVATE_NONPCM_WRITE_BACK_BS,
	ENUM_AI_PRIVATE_LOOPBACK_AO,
	ENUM_AI_PRIVATE_ADC_ANALOG,
	ENUM_AI_PRIVATE_MULTIPLE_ADC,
	ENUM_AI_PRIVATE_ADC_AMIC,     // 11
	ENUM_AI_PRIVATE_ADC_SWAP,
	ENUM_AI_PRIVATE_ADC_SET_VOLUME,
	ENUM_AI_PRIVATE_AUDIO_PROCESSING,
	ENUM_AI_PRIVATE_VOLUME_CTRL,
	ENUM_AI_PRIVATE_WRITE_BACK_SYSTEM_EXT,
	ENUM_AI_PRIVATE_HDMIRX_AUDIO_INFO_FRAME,
	ENUM_AI_PRIVATE_HACK_1KHZ_WITHOUT_HW = 12 + 6,
	ENUM_AI_PRIVATE_SPDIF_OPTICAL = 12 + 7,
	ENUM_AI_PRIVATE_HDMI_RX = 12 + 8,
	ENUM_AI_PRIVATE_SPDIF_COAXIAL = 12 + 9,
	ENUM_AI_PRIVATE_SPDIF_ARC = 12 + 10,
	ENUM_AI_PRIVATE_ADC_DMIC = 12 + 11,
	ENUM_AI_PRIVATE_TDM = 12 + 12,
	ENUM_AI_PRIVATE_ADC_DMIC_PACK = 12 + 13,
	ENUM_AI_PRIVATE_SELF_FLUSH = 12 + 14,
	ENUM_AI_PRIVATE_CONFIG_PIN_MUX = 12 + 15,
	ENUM_AI_PRIVATE_DUMP_NONPCM = 12 + 16,
	ENUM_AI_PRIVATE_DUAL_DMIC_AND_LOOPBACK = 12 + 17,
	ENUM_AI_PRIVATE_DUAL_DMIC_AND_LOOPBACK_FW = 12 + 18,
	ENUM_AI_PRIVATE_SPEECH_RECOGNITION_FROM_DMIC = 12 + 19,
	ENUM_AI_PRIVATE_TOTAL_NUM = 12 + 20,
};

enum AUDIO_VOLUME_CTRL {
	ENUM_AUDIO_VOLUME_CTRL_0_DB = 0,
	ENUM_AUDIO_VOLUME_CTRL_N1_DB = 0 + 1,
	ENUM_AUDIO_VOLUME_CTRL_N2_DB = 0 + 2,
	ENUM_AUDIO_VOLUME_CTRL_N3_DB = 0 + 3,
	ENUM_AUDIO_VOLUME_CTRL_N4_DB = 0 + 4,
	ENUM_AUDIO_VOLUME_CTRL_N5_DB = 0 + 5,
	ENUM_AUDIO_VOLUME_CTRL_N6_DB = 0 + 6,
	ENUM_AUDIO_VOLUME_CTRL_N7_DB = 0 + 7,
	ENUM_AUDIO_VOLUME_CTRL_N8_DB = 0 + 8,
	ENUM_AUDIO_VOLUME_CTRL_N9_DB = 0 + 9,
	ENUM_AUDIO_VOLUME_CTRL_N10_DB = 0 + 10,
	ENUM_AUDIO_VOLUME_CTRL_N11_DB = 0 + 11,
	ENUM_AUDIO_VOLUME_CTRL_N12_DB = 0 + 12,
	ENUM_AUDIO_VOLUME_CTRL_N13_DB = 0 + 13,
	ENUM_AUDIO_VOLUME_CTRL_N14_DB = 0 + 14,
	ENUM_AUDIO_VOLUME_CTRL_N15_DB = 0 + 15,
	ENUM_AUDIO_VOLUME_CTRL_N16_DB = 0 + 16,
	ENUM_AUDIO_VOLUME_CTRL_P1_DB = 256,  //17
	ENUM_AUDIO_VOLUME_CTRL_P2_DB = 256 + 1,
	ENUM_AUDIO_VOLUME_CTRL_P3_DB = 256 + 2,
	ENUM_AUDIO_VOLUME_CTRL_P4_DB = 256 + 3,
	ENUM_AUDIO_VOLUME_CTRL_P5_DB = 256 + 4,
	ENUM_AUDIO_VOLUME_CTRL_P6_DB = 256 + 5,
	ENUM_AUDIO_VOLUME_CTRL_P7_DB = 256 + 6,
	ENUM_AUDIO_VOLUME_CTRL_P8_DB = 256 + 7,
	ENUM_AUDIO_VOLUME_CTRL_P9_DB = 256 + 8,
	ENUM_AUDIO_VOLUME_CTRL_P10_DB = 256 + 9,
	ENUM_AUDIO_VOLUME_CTRL_P11_DB = 256 + 10,
	ENUM_AUDIO_VOLUME_CTRL_P12_DB = 256 + 11,
	ENUM_AUDIO_VOLUME_CTRL_P13_DB = 256 + 12,
	ENUM_AUDIO_VOLUME_CTRL_P14_DB = 256 + 13,
	ENUM_AUDIO_VOLUME_CTRL_P15_DB = 256 + 14,
	ENUM_AUDIO_VOLUME_CTRL_P16_DB = 256 + 15,  //32
};

enum AUDIO_ENUM_AI_LOOPBACK_DEV {
	ENUM_RPC_AI_LOOPBACK_HDMITX = 0,
	ENUM_RPC_AI_LOOPBACK_DAC = 0 + 1,
	ENUM_RPC_AI_LOOPBACK_FROM_AO_I2S = 0 + 2,
	ENUM_RPC_AI_LOOPBACK_TOTAL_NUM = 0 + 3,
};

enum ENUM_GBL_VAR_EQUALIZER_ID {
	ENUM_EQUALIZER_PP = 0,
	ENUM_EQUALIZER_MIC = 1,
	ENUM_EQUALIZER_AUX = 2,
	ENUM_EQUALIZER_AO = 3,
};

enum AIN_AUDIO_PROCESSING {
	ENUM_AIN_AUDIO_PROCESSING_NONE = 0,
	ENUM_AIN_AUDIO_PROCESSING_NO_INTERNAL_RING_BUF = 0 + 1,
	ENUM_AIN_AUDIO_PROCESSING = 0 + 2,
	ENUM_AIN_AUDIO_PROCESSING_DMIC_AND_LOOPBACK = 0 + 3,
	ENUM_AIN_AUDIO_PROCESSING_DMIC = 0 + 4,
	ENUM_AIN_AUDIO_PROCESSING_I2S = 0 + 5,
};

enum AUDIO_ENUM_DEC_PRIVAETINFO {
	ENUM_PRIVATEINFO_DEC_CHECK_B = 0,
	ENUM_PRIVATEINFO_DEC_SET_LIMITER_EN = 1,
	ENUM_PRIVATEINFO_DEC_CHECK_D6 = 1 + 1,
	ENUM_PRIVATEINFO_DEC_CHECK_DSD = 1 + 2,
	ENUM_PRIVATEINFO_DEC_SET_CODEC_KEY = 1 + 3,
	ENUM_PRIVATEINFO_DEC_SET_PASSTHROUGH_KEY = 1 + 4,
	ENUM_PRIVATEINFO_DEC_CHECK_DB_IDK_V2_3 = 1 + 5,
	ENUM_PRIVATEINFO_DEC_CHECK_SCPU_B = 1 + 6,
	ENUM_PRIVATEINFO_DEC_GET_ID = 1 + 7,
	ENUM_PRIVATEINFO_DEC_CHECK_DB_VALID = 1 + 8,
	ENUM_PRIVATEINFO_DEC_CLASSIFY_GROUP_B = 1 + 9,
	ENUM_PRIVATEINFO_DEC_CONFIG_CHIDX = 1 + 10,
	ENUM_PRIVATEINFO_DEC_SHARE_MEM = 1 + 11,
	ENUM_PRIVATEINFO_DEC_CONFIG_OUTRING_TYPE = 1 + 12,
	ENUM_PRIVATEINFO_DEC_CONFIG_LPCM_OUT = 1 + 13,
	ENUM_PRIVATEINFO_DEC_ALSA_CONFIG = 1 + 14,
};

struct AUDIO_CONFIG_COMMAND {
	enum AUDIO_CONFIG_CMD_MSG msgID;
	unsigned int value[6];
};

struct RPCRES_LONG {
	uint32_t result;
	int data;
};

struct RPC_DEFAULT_INPUT_T {
	unsigned int  info;
	struct RPCRES_LONG retval;
	uint32_t ret;
};

struct AUDIO_RPC_PRIVATEINFO_PARAMETERS {
	int instanceID;
	enum AUDIO_ENUM_PRIVAETINFO type;
	volatile int privateInfo[16];
};

struct AUDIO_RPC_PRIVATEINFO_RETURNVAL {
	int instanceID;
	volatile int privateInfo[16];
};

struct AUDIO_EQUALIZER_CONFIG {
	int instanceID;
	int gbl_var_eq_ID;
	unsigned char ena;
	struct AUDIO_RPC_EQUALIZER_MODE app_eq_config;
};

struct AUDIO_RPC_INSTANCE {
	int instanceID;
	int type;
};

struct RPC_CREATE_AO_AGENT_T {
	struct AUDIO_RPC_INSTANCE info;
	struct RPCRES_LONG retval;
	uint32_t ret;
};

struct RPC_CREATE_PCM_DECODER_CTRL_T {
	struct AUDIO_RPC_INSTANCE instance;
	struct RPCRES_LONG res;
	uint32_t ret;
};

struct AUDIO_RPC_RINGBUFFER_HEADER {
	int instanceID;
	int pinID;
	int pRingBufferHeaderList[8];
	int readIdx;
	int listSize;
};

// Ring Buffer header is the shared memory structure
struct RINGBUFFER_HEADER {
	unsigned int magic;   //Magic number
	unsigned int beginAddr;
	unsigned int size;
	unsigned int bufferID;  // RINGBUFFER_TYPE, choose a type from RINGBUFFER_TYPE

	unsigned int  writePtr;
	unsigned int  numOfReadPtr;
	unsigned int  reserve2;  //Reserve for Red Zone
	unsigned int  reserve3;  //Reserve for Red Zone

	unsigned int readPtr[4];

	int          fileOffset;
	int          requestedFileOffset;
	int          fileSize;

	int          bSeekable;  /* Can't be sought if data is streamed by HTTP */
/*
 * FileOffset:
 * the offset to the streaming file from the beginning of the file.
 * It is set by system to tell FW that the current streaming is starting from ��FileOffset�� bytes.
 * For example, the TIFF file display will set fileOffset to 0 at beginning.
 *
 * RequestedFileOffset:
 * the offset to be set by video firmware, to request system to seek to other place.
 * The initial is -1.When it is not equal to -1, that means FW side is requesting a new seek.
 *
 * FileSize:
 * file size. At current implementation, only TIFF decode needs the fileSize,
 * other decoding does not pay attention to this field
 *
 * the behavior for TIFF seek:
 * At the initial value, FileOffset = 0, or at any initial offset (for example, resume from bookmark), RequestedFileOffset=-1. FileSize= file size.
 * 1. If FW needs to perform seek operation, FW set RequestedFileOffset to the value it need to seek.
 * 2. Once system see RequestedOffset is not -1, system reset the ring buffer (FW need to make sure it will not use ring buffer after request the seek), set FileOffset to the new location (the value of RequestedFileOffset), then set RequestedOffset  to -1. From now on, system will stream data from byte FileOffset of the file.
 * 3. FW needs to wait until RequestedOffset== -1, then check the value inside FileOffset. If FileOffset is -1, that means read out of bound.
 * If system already finish the streaming before FW issue a seek, system will still continue polling.
 */
};

struct RPC_INITRINGBUFFER_HEADER_T {
	struct RPCRES_LONG ret;
	uint32_t res;
	struct AUDIO_RPC_RINGBUFFER_HEADER header;
};

struct AUDIO_RPC_CONNECTION {
	int srcInstanceID;
	int srcPinID;
	int desInstanceID;
	int desPinID;
	int mediaType;
};

struct RPC_CONNECTION_T {
	struct AUDIO_RPC_CONNECTION out;
	struct RPCRES_LONG ret;
	uint32_t res;
};

struct RPC_TOAGENT_T {
	int inst_id;
	struct RPCRES_LONG retval;
	uint32_t res;
};

struct RPC_TOAGENT_PAUSE_T {
	int inst_id;
	uint32_t retval;
	uint32_t res;
};

struct AUDIO_RPC_SENDIO {
	int instanceID;
	int pinID;
};

struct RPC_TOAGENT_FLASH_T {
	struct RPCRES_LONG retval;
	uint32_t res;
	struct AUDIO_RPC_SENDIO sendio;
};

struct AUDIO_INBAND_CMD_PKT_HEADER {
	enum AUDIO_INBAND_CMD_TYPE type;
	int size;
};

struct AUDIO_DEC_EOS {
	struct AUDIO_INBAND_CMD_PKT_HEADER header;
	unsigned int wPtr;
	int EOSID;  /* ID associated with command */
};

struct AUDIO_DEC_NEW_FORMAT {
	struct AUDIO_INBAND_CMD_PKT_HEADER header;
	unsigned int wPtr;
	enum AUDIO_DEC_TYPE audioType;
	int privateInfo[8];  // note: privateinfo[6] is used for choosing decoder sync pts method
};

struct AUDIO_DEC_PTS_INFO {
	struct AUDIO_INBAND_CMD_PKT_HEADER header;
	unsigned int               wPtr;
	unsigned int               PTSH;
	unsigned int               PTSL;
};

struct RPC_TOAGENT_STOP_T {
	struct RPCRES_LONG retval;
	uint32_t         res;
	int        instanceID;
};

struct RPC_TOAGENT_DESTROY_T {
	struct RPCRES_LONG retval;
	uint32_t         res;
	int        instanceID;
};

struct RPC_GET_VOLUME_T {
	struct RPCRES_LONG res;
	uint32_t ret;
	struct AUDIO_RPC_PRIVATEINFO_PARAMETERS  param;
};

struct AUDIO_GENERAL_CONFIG {
	char interface_en;
	char channel_in;
	char count_down_rec_en;
	int count_down_rec_cyc;
};

struct AUDIO_SAMPLE_INFO {
	int sampling_rate;
	int PCM_bitnum;
};

struct AUDIO_ADC_CONFIG {
	struct AUDIO_GENERAL_CONFIG audioGeneralConfig;
	struct AUDIO_SAMPLE_INFO sampleInfo;
};

struct AUDIO_CONFIG_ADC {
	int instanceID;
	struct AUDIO_ADC_CONFIG adcConfig;
};

struct AUDIO_RPC_REFCLOCK {
	int instanceID;
	int pRefClockID;
	int pRefClock;
};

struct AUDIO_RPC_REFCLOCK_T {
	int instanceID;
	int pRefClockID;
	int pRefClock;
	struct RPCRES_LONG ret;
	uint32_t res;
};

struct AUDIO_RPC_FOCUS {
	int instanceID;
	int focusID;
};

struct AUDIO_RPC_FOCUS_T {
	int instanceID;
	int focusID;
	struct RPCRES_LONG ret;
	uint32_t res;
};

struct AUDIO_OUT_GENERAL_CONFIG {
	char interface_en;
	char channel_out;
	char count_down_play_en;
	int count_down_play_cyc;
};

struct AUDIO_OUT_CS_INFO {
	char non_pcm_valid;
	char non_pcm_format;
	int audio_format;
	char spdif_consumer_use;
	char copy_right;
	char pre_emphasis;
	char stereo_channel;
};

struct AUDIO_DAC_CONFIG {
	struct AUDIO_OUT_GENERAL_CONFIG audioGeneralConfig;
	struct AUDIO_SAMPLE_INFO sampleInfo;
};

struct AUDIO_OUT_SPDIF_CONFIG {
	struct AUDIO_OUT_GENERAL_CONFIG audioGeneralConfig;
	struct AUDIO_SAMPLE_INFO sampleInfo;
	struct AUDIO_OUT_CS_INFO out_cs_info;
};

struct AUDIO_CONFIG_DAC_I2S {
	int instanceID;
	struct AUDIO_DAC_CONFIG dacConfig;
};

struct AUDIO_CONFIG_DAC_I2S_T {
	int instanceID;
	struct AUDIO_DAC_CONFIG dacConfig;
	uint32_t res;
};

struct AUDIO_CONFIG_DAC_SPDIF {
	int instanceID;
	struct AUDIO_OUT_SPDIF_CONFIG spdifConfig;
};

struct AUDIO_CONFIG_DAC_SPDIF_T {
	int instanceID;
	struct AUDIO_OUT_SPDIF_CONFIG spdifConfig;
	uint32_t res;
};

struct AUDIO_RINGBUF_PTR {
	int base;
	int limit;
	int cp;
	int rp;
	int wp;
};

struct AUDIO_RINGBUF_PTR_64 {
	unsigned long base;
	unsigned long limit;
	unsigned long cp;
	unsigned long rp;
	unsigned long wp;
};

struct ALSA_MEM_INFO {
	phys_addr_t pPhy;
	unsigned int *pVirt;
	unsigned int size;
};

struct ALSA_LATENCY_INFO {
	unsigned int latency;
	unsigned int ptsL;
	unsigned int ptsH;
	unsigned int sum;     // latency + ptsL
	unsigned int decin_wp;
	unsigned int sync;
	unsigned int dec_in_delay;
	unsigned int dec_out_delay;
	unsigned int ao_delay;
	int rvd[8];
};

struct AUDIO_RPC_AIO_PRIVATEINFO_PARAMETERS {
	int instanceID;
	enum AUDIO_ENUM_AIO_PRIVAETINFO type;
	int argateInfo[16];
};

struct AUDIO_RPC_DEC_PRIVATEINFO_PARAMETERS {
	long instanceID;
	enum AUDIO_ENUM_DEC_PRIVAETINFO type;
	long privateInfo[16];
};

/* RTK sound card */
struct RTK_snd_card {
	struct snd_card *card;
	spinlock_t mixer_lock;
	int mixer_volume[MIXER_ADDR_LAST+1][2];
	int mixer_change;
	int capture_source[MIXER_ADDR_LAST+1][2];
	int capture_change;
	struct work_struct work_volume;
	struct mutex rpc_lock;
	struct snd_pcm *pcm;
	struct snd_compr *compr;
};

/* RTK PCM instance */
struct snd_card_RTK_pcm {
/******************************************************************************************************************
 ** CAN'T change the order of the following variables, bcz AO(on SCPU) will refer RINGBUFFER_HEADER decOutRing[8] *
 ******************************************************************************************************************/
	struct RINGBUFFER_HEADER decOutRing[8];    /* big endian, in DEC-AO path, share with DEC and AO */
	struct RTK_snd_card *card;
	struct snd_pcm_substream *substream;
	struct RINGBUFFER_HEADER decInbandRing;    /* big endian, in DEC-AO path, inband ring of DEC */
	struct RINGBUFFER_HEADER decInRing[1];     /* big endian, uncache, in DEC-AO path, inring of DEC */
	struct RINGBUFFER_HEADER decInRing_LE[1];  /* little endian, uncache, duplication of nHWInring */

	snd_pcm_uframes_t nHWPtr;           /* in DEC-AO path, rp of in_ring of DEC, (0,1, ..., ,runntime->buffer_size-1) */
	snd_pcm_uframes_t nPreHWPtr;
	snd_pcm_uframes_t nPre_appl_ptr;
	snd_pcm_uframes_t nHWReadSize;      /* less than runntime->period_size */
	snd_pcm_uframes_t nTotalRead;
	snd_pcm_uframes_t nTotalWrite;

#ifdef DEBUG_RECORD
	struct file *fp;
	loff_t pos;                         /* The param for record data send to alsa */
	mm_segment_t fs;
#endif

	struct hrtimer hr_timer;           /* Hr timer for playback */
	enum hrtimer_restart enHRTimer;    /* Hr timer state */
	ktime_t ktime;                     /* Ktime for hr timer */
	enum SND_REALTEK_EOS_STATE_T nEOSState;
	int DECAgentID;
	int DECpinID;
	int AOAgentID;
	int AOpinID;
	int volume;
	int bInitRing;
	int bHWinit;
	int last_channel;
	int ao_decode_lpcm;
	unsigned int decInbandData[64];     //inband ring
	unsigned int *decOutData[8];        //decoder Output data
	int *g_ShareMemPtr;
	struct ALSA_LATENCY_INFO *g_ShareMemPtr2;
	struct ALSA_LATENCY_INFO *g_ShareMemPtr3;
	unsigned int nPeriodBytes;
	unsigned int nRingSize;          // bytes
	unsigned int dbg_count;
	unsigned int audio_count;
	phys_addr_t phy_decOutData[8];   // physical address of Output data
	phys_addr_t phy_addr;            // physical address of struct snd_card_RTK_pcm;
	phys_addr_t phy_addr_rpc;    // physical address for doing suspend
	phys_addr_t g_ShareMemPtr_dat;   // physical address for latency
	phys_addr_t g_ShareMemPtr_dat2;
	phys_addr_t g_ShareMemPtr_dat3;
	struct RINGBUFFER_HEADER decOutRing_LE[8];    /* little endian, in DEC-AO path, share with DEC and AO */
	struct dma_buf *rpc_dmabuf;
	struct dma_buf *rpc_dmabuf_rpc;    // dma buffer for doing suspend
	struct dma_buf *dec_out_rpc_dmabuf[8]; // dma buffer for decoder out
	struct dma_buf *g_ShareMemPtr_dat_rpc_dmabuf;
	struct dma_buf *g_ShareMemPtr_dat2_rpc_dmabuf;
	struct dma_buf *g_ShareMemPtr_dat3_rpc_dmabuf;
	void *vaddr_rpc;  //virtual address for doing suspend
	struct AUDIO_RPC_OUT_PARAMETER *ao_paramter;
};

struct snd_card_RTK_capture_pcm {
	struct RTK_snd_card *card;
	struct snd_pcm_substream *substream;
	struct RINGBUFFER_HEADER nAIRing[8];       /* big endian */
	struct RINGBUFFER_HEADER nAIRing_LE[8];    /* little endian */
	struct RINGBUFFER_HEADER nLPCMRing;        /* big endian */
	struct RINGBUFFER_HEADER nLPCMRing_LE;     /* little endian */
	struct RINGBUFFER_HEADER nPTSRingHdr;      /* big endian */
	struct RINGBUFFER_HEADER decInRing[1];     /* big endian */
	struct RINGBUFFER_HEADER decInRing_LE[1];  /* little endian */
	snd_pcm_uframes_t nAIRingWp;
	snd_pcm_uframes_t nAIRingPreWp;
	snd_pcm_uframes_t nTotalWrite;
	enum AUDIO_FORMAT_OF_AI_SEND_TO_ALSA nAIFormat;

	struct hrtimer hr_timer;           /* Hr timer for playback */
	enum hrtimer_restart enHRTimer;    /* Hr timer state */
	ktime_t ktime;                     /* Ktime for hr timer */
	int AIAgentID;
	int AOAgentID;
	int AOpinID;
	int bInitRing;
	int source_in;
	int *pAIRingData[8]; // kernel virtual address
	unsigned int *pLPCMData;
	unsigned int nPeriodBytes;
	unsigned int nFrameBytes;
	unsigned int nRingSize; // bytes
	unsigned int nLPCMRingSize;
	phys_addr_t phy_pAIRingData[8]; //physical address of ai data
	phys_addr_t phy_pLPCMData;      //physical address of lpcm data
	phys_addr_t phy_addr;           //physical addresss of struct snd_card_RTK_capture_pcm;
	phys_addr_t phy_addr_rpc;   //physical address for doing suspend
	struct ALSA_MEM_INFO nPTSMem;
	struct AUDIO_RINGBUF_PTR_64 nPTSRing;
	struct timespec64 ts;
	struct dma_buf *rpc_dmabuf;
	struct dma_buf *rpc_dmabuf_rpc;   //dma buffer for doing suspend
	struct dma_buf *enc_in_rpc_dmabuf[2]; //dma buffer for encoder in
	struct dma_buf *enc_lpcm_rpc_dmabuf;  //dma buffer for lpcm
	void *vaddr_rpc;  //virtual address for doing suspend
};


/************************************************************************/
/* PROTOTYPE                                                            */
/************************************************************************/
int snd_realtek_hw_ring_write(struct RINGBUFFER_HEADER *ring, void *data, int len, unsigned int offset);
int writeInbandCmd(struct snd_card_RTK_pcm *dpcm, void *data, int len);
uint64_t snd_card_get_90k_pts(void);

// RPC function
int RPC_TOAGENT_CHECK_AUDIO_READY(phys_addr_t paddr, void *vaddr);
int RPC_TOAGENT_SEND_AUDIO_VERSION(phys_addr_t paddr, void *vaddr, enum OMX_AUDIO_VERSION version);
int RPC_TOAGENT_CONNECT_SVC(phys_addr_t paddr, void *vaddr, struct AUDIO_RPC_CONNECTION *pconnection);
int RPC_TOAGENT_DESTROY_SVC(phys_addr_t paddr, void *vaddr, int instanceID);
int RPC_TOAGENT_FLUSH_SVC(phys_addr_t paddr, void *vaddr, struct AUDIO_RPC_SENDIO *sendio);
int RPC_TOAGENT_INBAND_EOS_SVC(struct snd_card_RTK_pcm *dpcm);
int RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(phys_addr_t paddr, void *vaddr, struct AUDIO_RPC_RINGBUFFER_HEADER *header, int buffer_count);
int RPC_TOAGENT_PAUSE_SVC(phys_addr_t paddr, void *vaddr, int instance_id);
int RPC_TOAGENT_RUN_SVC(phys_addr_t paddr, void *vaddr, int instance_id);
int RPC_TOAGENT_STOP_SVC(phys_addr_t paddr, void *vaddr, int instanceID);
int RPC_TOAGENT_PP_INIT_PIN_SVC(phys_addr_t paddr, void *vaddr, int instanceID);
int RPC_TOAGENT_CREATE_AO_AGENT(phys_addr_t paddr, void *vaddr, int *aoId, int pinId);
int RPC_TOAGENT_CREATE_PP_AGENT(phys_addr_t paddr, void *vaddr, int *ppId, int *pinId);
int RPC_TOAGENT_GET_AO_FLASH_PIN(phys_addr_t paddr, void *vaddr, int AOAgentID);
int RPC_TOAGENT_GET_GLOBAL_PP_PIN(phys_addr_t paddr, void *vaddr, int *pinId);
int RPC_TOAGENT_CREATE_DECODER_AGENT(phys_addr_t paddr, void *vaddr, int *decId, int *pinId);
int RPC_TOAGENT_SET_AO_FLASH_VOLUME(phys_addr_t paddr, void *vaddr,	struct snd_card_RTK_pcm *dpcm);
int RPC_TOAGENT_RELEASE_AO_FLASH_PIN(phys_addr_t paddr, void *vaddr, int AOAgentID, int AOpinID);
int RPC_TOAGENT_SET_TRUEHD_ERR_SELF_RESET(phys_addr_t paddr, void *vaddr, bool isON);
int RPC_TOAGENT_SET_VOLUME(int volume);
int RPC_TOAGENT_GET_VOLUME(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_pcm *mars);
int RPC_TOAGENT_PUT_SHARE_MEMORY(phys_addr_t paddr, void *vaddr, void *p, int type);
int RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY(phys_addr_t paddr, void *vaddr, void *p, void *p2, int decID, int aoID, int type);
int RPC_TOAGENT_CREATE_AI_AGENT(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_AI_CONNECT_ALSA(phys_addr_t paddr, void *vaddr, struct snd_pcm_runtime *runtime);
int RPC_TOAGENT_AI_DISCONNECT_ALSA_AUDIO(phys_addr_t paddr, void *vaddr, struct snd_pcm_runtime *runtime);
int RPC_TOAGENT_SWITCH_FOCUS(phys_addr_t paddr, void *vaddr, struct AUDIO_RPC_FOCUS *focus);
int RPC_TOAGENT_DAC_I2S_CONFIG(phys_addr_t paddr, void *vaddr, struct AUDIO_CONFIG_DAC_I2S *config);
int RPC_TOAGENT_DAC_SPDIF_CONFIG(phys_addr_t paddr, void *vaddr, struct AUDIO_CONFIG_DAC_SPDIF *config);
int RPC_TOAGENT_SETREFCLOCK(phys_addr_t paddr, void *vaddr, struct AUDIO_RPC_REFCLOCK *pClock);
int RPC_TOAGENT_AI_CONFIG_HDMI_RX_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_AI_CONFIG_I2S_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_AI_CONFIG_AUDIO_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_AI_CONFIG_I2S_LOOPBACK_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_AI_CONFIG_DMIC_PASSTHROUGH_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_DESTROY_AI_FLOW_SVC(phys_addr_t paddr, void *vaddr, int instance_id);
int RPC_TOAGENT_AI_CONFIG_NONPCM_IN(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_SET_AI_FLASH_VOLUME(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm, unsigned int volume);
int RPC_TOAGENT_SET_SOFTWARE_AI_FLASH_VOLUME(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm, unsigned int volume);
int RPC_TOAGENT_SET_LOW_WATER_LEVEL(phys_addr_t paddr, void *vaddr, bool isLowWater);
int RPC_TOAGENT_GET_AI_AGENT(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_SET_EQ(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_pcm *dpcm, struct AUDIO_RPC_EQUALIZER_MODE *equalizer_mode);
int RPC_TOAGENT_AO_CONFIG_WITHOUT_DECODER(phys_addr_t paddr, void *vaddr, struct snd_pcm_runtime *runtime);
int RPC_TOAGENT_CREATE_GLOBAL_AO(phys_addr_t paddr, void *vaddr, int *aoId);
int RPC_TOAGENT_AI_CONNECT_AO(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_capture_pcm *dpcm);
int RPC_TOAGENT_SET_MAX_LATENCY(phys_addr_t paddr, void *vaddr, struct snd_card_RTK_pcm *dpcm);

#endif //SND_REALTEK_H
