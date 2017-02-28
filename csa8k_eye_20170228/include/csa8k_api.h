/*
*	Copyright (C) 2016 ShangHai Sino-telecom Technology, Inc.
*/

#ifndef CSA8K_API_H
#define CSA8K_API_H

#include "visa.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CHANNEL_MAX	8
#define MEAS_MAX		8
#define CMD_STR_MAX	256
#define RES_STR_MAX	256
#define IDN_STR_MAX	256
#define SHT_STR_MAX	64
static char cmd_global[SHT_STR_MAX];
typedef enum {
	CMD_SUCCESS = 0,
	CMD_ERROR = 1,
} CMD_RET;

typedef enum {
	EYE_WIDTH = 1,
	EYE_HEIGHT = 2,
	EYE_HIGH = 3,
	EYE_LOW = 4,
	EYE_AMPLITUDE = 5,
	EYE_PCROSS = 6,
	EYE_NCROSS = 7,
	EYE_EXTICTRATIO = 8,
	EYE_QFACTOR = 9,
	EYE_AOPTPWRDBM = 10,
    EYE_RMSJITTER = 11,
    EYE_PKPKJITTER = 12,
    EYE_EXTINCTDB = 13,
    EYE_PCTCROSS = 14,
} MEASUREMENT_TYPE;

typedef enum {
	OFF	= 0,
	ON	= 1,
} STATE;

typedef enum {
	FILTER_OC48 = 1,
} VERT_FILTER;

typedef enum {
	MASK_OC48 = 1,
} MASK_STANDARD;

typedef enum {
	PNG = 1,
	JPEG = 2,
	BMP = 3,
	TIFF = 4,
	TARGA = 5,
} HARDCOPY_FORMAT;

typedef struct meas_config_vert {
    int     sel_chx_state[CHANNEL_MAX];		//define sel_chx_state[0] as ch1 state
    int     chx_wlength[CHANNEL_MAX];		//define chx_wlength[0] as ch1 wave length
	char	chx_filter[CHANNEL_MAX][SHT_STR_MAX];			//define *chx_filter[0] as ch1 filter
} meas_config_vert_t;

typedef struct meas_config_mask {
	char	mask_source[SHT_STR_MAX];
    int     mask_count_state;
	char	mask_standard[SHT_STR_MAX];
    int 	mask_margins_state;
    double 	mask_margins_percent;
} meas_config_mask_t;

typedef struct meas_config_acq {
	char	acq_sa_mode[SHT_STR_MAX];		//acquire:stopafter:mode
	char	acq_sa_condition[SHT_STR_MAX];
    int     acq_sa_count;
} meas_config_acq_t;

typedef struct meas_config_trig {
	char	trig_src[SHT_STR_MAX];
	char	trig_clkrec_src[SHT_STR_MAX];
	char	trig_chx_clkrec_value[CHANNEL_MAX][SHT_STR_MAX];		//define *trig_chx_clkrec_value[0] as ch1 clock recover value
} meas_config_trig_t;

typedef struct meas_config {
	int		config_index;
    char	config_name[SHT_STR_MAX];
    char	hardcopy_fmt[SHT_STR_MAX];
	meas_config_vert_t	meas_config_vert;
	meas_config_mask_t	meas_config_mask;
    meas_config_acq_t	meas_config_acq;
    meas_config_trig_t	meas_config_trig;
} meas_config_t;

typedef struct meas_entry {
	int			meas_index;
	int			meas_type;
    double		meas_value;
	list_head_t	list;
} meas_entry_t;

//connect initialized
typedef struct gpib_proc {
    int         pid;
	ViSession 	vi;
	ViSession 	defaultRM;
} gpib_proc_t;

//initialize
int gpib_connect_initialize(const int gpib_id, const int gpib_addr, gpib_proc_t *gpib_proc, char* idn);
int gpib_connect_close(gpib_proc_t *gpib_proc);

//get idn
int get_idn(ViSession *vi, char *idn);
int reset_factory(ViSession *vi);

//send and read common command
int send_cmd(ViSession *vi, const char *cmd);
int read_rps(ViSession *vi, char *rps);

//configure vert
int set_select_chx(ViSession *vi, meas_config_t *meas_config, const int channel);
int set_deselect_chx(ViSession *vi, meas_config_t *meas_config, const int channel);
int get_select_chx(ViSession *vi, meas_config_t *meas_config, const int channel);
int set_chx_wlength_value(ViSession *vi, meas_config_t *meas_config, const int channel, const int wlength);
int get_chx_wlength_value(ViSession *vi, meas_config_t *meas_config, const int channel);
int set_chx_filter_value(ViSession *vi, meas_config_t *meas_config, const int channel,const char *filter);
int get_chx_filter_value(ViSession *vi, meas_config_t *meas_config, const int channel);
//int get_chx_filter_value_list(char *filter_list_ptr[]);

//configure mask
int set_mask_source(ViSession *vi, meas_config_t *meas_config, const char *source);
int get_mask_source(ViSession *vi, meas_config_t *meas_config);
int set_mask_count_state(ViSession *vi, meas_config_t *meas_config, const int state);
int get_mask_count_state(ViSession *vi, meas_config_t *meas_config);
int set_mask_standard(ViSession *vi, meas_config_t *meas_config, const char *standard);
int get_mask_standard(ViSession *vi, meas_config_t *meas_config);
int set_mask_margins_state(ViSession *vi, meas_config_t *meas_config, const int state);
int get_mask_margins_state(ViSession *vi, meas_config_t *meas_config);
int set_mask_margins_percent(ViSession *vi, meas_config_t *meas_config, const double percent);
int get_mask_margins_percent(ViSession *vi, meas_config_t *meas_config);
int set_mask_autoset(ViSession *vi, meas_config_t *meas_config);
int get_mask_chx_count(ViSession *vi, meas_config_t *meas_config, const int channel, unsigned int *result);
int get_mask_total_count(ViSession *vi, meas_config_t *meas_config, unsigned int *result);

//configure acq
int set_acq_stopafter_mode(ViSession *vi, meas_config_t *meas_config, const char *mode);
int get_acq_stopafter_mode(ViSession *vi, meas_config_t *meas_config);
int set_acq_stopafter_condition(ViSession *vi, meas_config_t *meas_config, const char *condition);
int get_acq_stopafter_condition(ViSession *vi, meas_config_t *meas_config);
int set_acq_stopafter_count(ViSession *vi, meas_config_t *meas_config, const int count);
int get_acq_stopafter_count(ViSession *vi, meas_config_t *meas_config);
int set_acq_state_runstop(ViSession *vi, meas_config_t *meas_config, const int state);

//configure trig
int set_trig_source(ViSession *vi, meas_config_t *meas_config, const char *source);
int set_trig_clkrec_source(ViSession *vi, meas_config_t *meas_config, const char* source);
int get_trig_clkrec_source(ViSession *vi, meas_config_t *meas_config);
int set_trig_chx_clkrec_value(ViSession *vi, meas_config_t *meas_config, const int channel, const char *value);
int get_trig_chx_clkrec_value(ViSession *vi, meas_config_t *meas_config, const int channel);

//measurement
int set_measurement_measx_type(ViSession *vi, meas_entry_t *meas_ptr);
int meas_entry_init(meas_entry_t *meas_ptr, const int index, const int type);
//int get_measurement_measx_type(int *type_ptr);
int get_measurement_meax_value(ViSession *vi, meas_entry_t *meas_ptr, const int index);
int set_measurement_select_meas(ViSession *vi, meas_config_t *meas_config, const int measx, const char *type);
int set_measurement_measx_sourcetype(ViSession *vi, meas_config_t *meas_config, const int measx, const int source, const char *type);
int set_measurement_readout(ViSession *vi, int state);

//hardcopy
int set_hardcopy_format(ViSession *vi, meas_config_t *meas_config, char *format);
int csa8k_hardcopy(ViSession *vi, char *name);

//waveform database
int set_wfmdbx_display(ViSession *vi, const int index, const int state);

#ifdef __cplusplus
}
#endif


#endif // CSA8K_API_H
