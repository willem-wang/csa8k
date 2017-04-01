/*
*	Copyright (C) 2016 ShangHai Sino-telecom Technology, Inc.
*/

#include <stdio.h>

#include "../include/list.h"
#include "../include/visa.h"
#include "../include/csa8k_api.h"

int gpib_connect_initialize(const int gpib_id, const int gpib_addr, gpib_proc_t *gpib_proc, char* idn)
{
	int		str_len = 0;
	ViStatus 	status = 0;
	char		cmd_str[CMD_STR_MAX] = {0};
	
	str_len = snprintf(cmd_str, CMD_STR_MAX, "GPIB%d::%d::INSTR", gpib_id, gpib_addr);
	if (str_len == 0)
		return CMD_ERROR;

	status = viOpenDefaultRM(&gpib_proc->defaultRM);
	if (status != VI_SUCCESS) {
		snprintf(idn, IDN_STR_MAX, "%%Open VISA Resource Manager Fail!\n");
		return CMD_ERROR;
	}
		
	status = viOpen(gpib_proc->defaultRM, cmd_str, VI_NULL, VI_NULL, &gpib_proc->vi);
	if (status != VI_SUCCESS) {
		snprintf(idn, IDN_STR_MAX, "%%Open Instrument Fail!\n");
		return CMD_ERROR;
	}
	
	if ( get_idn(&gpib_proc->vi, idn) != CMD_SUCCESS)
		return CMD_ERROR;

	return CMD_SUCCESS;
}

int gpib_connect_close(gpib_proc_t *gpib_proc)
{
	ViStatus status = 0;
	
	status = viClose (gpib_proc->vi);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	
	status = viClose (gpib_proc->defaultRM);
	if (status != VI_SUCCESS)
		return CMD_ERROR;

	return CMD_SUCCESS;
}

int get_idn(ViSession *vi, char *idn)
{
	ViStatus 	status = 0;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	viPrintf(*vi, "*IDN?\n");
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viScanf(*vi, "%t", idn);
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int reset_factory(ViSession *vi)
{
	ViStatus 	status = 0;

	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, "*RST\n");
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int send_cmd(ViSession *vi, const char *cmd)
{
	int		str_len = 0;
	char 	cmd_str[CMD_STR_MAX] = {0};
	ViStatus 	status = 0;

	if (cmd == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "%s\n", cmd);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int read_rps(ViSession *vi, char *rps)
{	
	ViStatus status = 0;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS) {
		snprintf(rps, RES_STR_MAX, "error\n");
		return CMD_ERROR;
	}
	viScanf(*vi, "%t", rps);
	viUnlock(*vi);

	return CMD_SUCCESS;
}

//vert->waveform->channel x state
int set_select_chx(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "select:ch%d 1\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	meas_config->meas_config_vert.sel_chx_state[channel - 1] = ON;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int set_deselect_chx(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "select:ch%d 0\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	meas_config->meas_config_vert.sel_chx_state[channel - 1] = OFF;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int get_select_chx(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	int	state = OFF;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;
	
	str_len = snprintf(cmd_str, CMD_STR_MAX, "select:ch%d?\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%d", state);
	meas_config->meas_config_vert.sel_chx_state[channel - 1] = state;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

//vert->setup->wave length
int set_chx_wlength_value(ViSession *vi, meas_config_t *meas_config, const int channel, const int wlength)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "ch%d:wlength:value %d\n", channel, wlength);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	meas_config->meas_config_vert.chx_wlength[channel - 1] = wlength;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int get_chx_wlength_value(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	int	wlength = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;
	
	str_len = snprintf(cmd_str, CMD_STR_MAX, "ch%d:wlength:value?\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%d", wlength);
	meas_config->meas_config_vert.chx_wlength[channel - 1] = wlength;
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//vert->signal conditioning->filter
int set_chx_filter_value(ViSession *vi, meas_config_t *meas_config, const int channel, const char *filter)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (filter == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "ch%d:filter:value %s\n", channel, filter);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_vert.chx_filter[channel - 1], SHT_STR_MAX, filter);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_chx_filter_value(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	char filter[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "ch%d:filter:value?\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", filter);
	snprintf(meas_config->meas_config_vert.chx_filter[channel - 1], SHT_STR_MAX, filter);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}
/*
int get_chx_filter_value_list(char *filter_list_ptr[])
{
	return CMD_SUCCESS;
}
*/
//mask->source->channel
int set_mask_source(ViSession *vi, meas_config_t *meas_config, const char *source)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (source == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:source %s\n", source);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_mask.mask_source, SHT_STR_MAX, source);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_mask_source(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char source[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:source?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", source);
	snprintf(meas_config->meas_config_mask.mask_source, SHT_STR_MAX, source);
	viUnlock(*vi);

	return CMD_SUCCESS;
}

//mask->source->mask counts state
int set_mask_count_state(ViSession *vi, meas_config_t *meas_config, const int state)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:count:state %d\n", state);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	meas_config->meas_config_mask.mask_count_state = state;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int get_mask_count_state(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	int	state = OFF;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:count:state?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%d", state);
	meas_config->meas_config_mask.mask_count_state = state;
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//mask->source->comm standard
int set_mask_standard(ViSession *vi, meas_config_t *meas_config, const char *standard)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (standard == NULL)
		return CMD_ERROR;
    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:standard %s\n", standard);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_mask.mask_standard, SHT_STR_MAX, standard);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_mask_standard(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char standard[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:standard?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", standard);
	snprintf(meas_config->meas_config_mask.mask_standard, SHT_STR_MAX, standard);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}
//mask->mask margins->on
int set_mask_margins_state(ViSession *vi, meas_config_t *meas_config, const int state)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:margin:state %d\n", state);
    if (str_len == 0){
        return CMD_ERROR;
    }

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS){
        return CMD_ERROR;
    }
    viPrintf(*vi, cmd_str);
    meas_config->meas_config_mask.mask_margins_state = state;
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int get_mask_margins_state(ViSession *vi, meas_config_t *meas_config)
{
    int	str_len = 0;
    int	state = OFF;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:margin:state?\n");
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viScanf(*vi, "%d", state);
    meas_config->meas_config_mask.mask_margins_state = state;
    viUnlock(*vi);

    return CMD_SUCCESS;
}
//mask->mask margins->margin
int set_mask_margins_percent(ViSession *vi, meas_config_t *meas_config, const double percent)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:margin:percent %lf\n", percent);
    if (str_len == 0){
        return CMD_ERROR;
    }

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS){
        return CMD_ERROR;
    }
    viPrintf(*vi, cmd_str);
    meas_config->meas_config_mask.mask_margins_percent = percent;
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int get_mask_margins_percent(ViSession *vi, meas_config_t *meas_config)
{
    int	str_len = 0;
    double	state = OFF;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:margin:percent?\n");
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viScanf(*vi, "%lf", state);
    meas_config->meas_config_mask.mask_margins_percent = state;
    viUnlock(*vi);

    return CMD_SUCCESS;
}
//mask->autoset
int set_mask_autoset(ViSession *vi, meas_config_t *meas_config)
{
    int str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "autoset execute\n");
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int get_mask_chx_count(ViSession *vi, meas_config_t *meas_config, const int channel, unsigned int *result)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:mask%d:count?\n",channel);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viScanf(*vi, "%d", result);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int get_mask_total_count(ViSession *vi, meas_config_t *meas_config, unsigned int *result)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "mask:count:total?\n");
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viScanf(*vi, "%d", result);
    viUnlock(*vi);

    return CMD_SUCCESS;
}
//acq->stop after->mode
int set_acq_stopafter_mode(ViSession *vi, meas_config_t *meas_config, const char *mode)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (mode == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:mode %s\n", mode);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_acq.acq_sa_mode, SHT_STR_MAX, mode);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_acq_stopafter_mode(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char	mode[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:mode?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", mode);
	snprintf(meas_config->meas_config_acq.acq_sa_mode, SHT_STR_MAX, mode);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//acq->stop after->condition
int set_acq_stopafter_condition(ViSession *vi, meas_config_t *meas_config, const char *condition)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (condition == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:condition %s\n", condition);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_acq.acq_sa_condition, SHT_STR_MAX, condition);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_acq_stopafter_condition(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char	condition[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:condition?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", condition);
	snprintf(meas_config->meas_config_acq.acq_sa_condition, SHT_STR_MAX, condition);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//acq->stop after->count value
int set_acq_stopafter_count(ViSession *vi, meas_config_t *meas_config, const int count)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:count %d\n", count);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	meas_config->meas_config_acq.acq_sa_count = count;	
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_acq_stopafter_count(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	int	count = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "acquire:stopafter:count?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%d", count);
	meas_config->meas_config_acq.acq_sa_count = count;	
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//trig->trigger source
int set_trig_source(ViSession *vi, meas_config_t *meas_config, const char *source)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	if (source == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:source %s\n", source);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_trig.trig_src, SHT_STR_MAX, source);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_trig_source(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char	source[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:source?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", source);
	snprintf(meas_config->meas_config_trig.trig_src, SHT_STR_MAX, source);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//trig->trigger source->clock recovery source
int set_trig_clkrec_source(ViSession *vi, meas_config_t *meas_config, const char* source)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;
	
	if (source == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:clkrec:source %s\n", source);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_trig.trig_clkrec_src, SHT_STR_MAX, source);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int get_trig_clkrec_source(ViSession *vi, meas_config_t *meas_config)
{
	int	str_len = 0;
	char	source[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:clkrec:source?\n");
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", source);
	snprintf(meas_config->meas_config_trig.trig_clkrec_src, SHT_STR_MAX, source);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

//trig->trigger source->clock recovery->channel x value
int set_trig_chx_clkrec_value(ViSession *vi, meas_config_t *meas_config, const int channel, const char *value)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;
	
	if (value == NULL)
		return CMD_ERROR;
	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:ch%d:clkrec:value %s\n", channel, value);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->meas_config_trig.trig_chx_clkrec_value[channel - 1], SHT_STR_MAX, value);
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int get_trig_chx_clkrec_value(ViSession *vi, meas_config_t *meas_config, const int channel)
{
	int	str_len = 0;
	char	value[SHT_STR_MAX] = {0};
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "trigger:ch%d:clkrec:value?\n", channel);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%s", value);
	snprintf(meas_config->meas_config_trig.trig_chx_clkrec_value[channel - 1], SHT_STR_MAX, value);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int set_acq_state_runstop(ViSession *vi, meas_config_t *meas_config, const int state)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "ACQUIRE:STATE %d\n", state);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

//meas->meas x->measurement type
int set_measurement_measx_type(ViSession *vi, meas_entry_t *meas_ptr)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;
	
	switch(meas_ptr->meas_type) {
		case EYE_WIDTH:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type eyewidth\n", meas_ptr->meas_index);
			break;
			
		case EYE_HEIGHT:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type eyeheight\n", meas_ptr->meas_index);
			break;
			
		case EYE_HIGH:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type high\n", meas_ptr->meas_index);
			break;
			
		case EYE_LOW:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type low\n", meas_ptr->meas_index);
			break;
			
		case EYE_AMPLITUDE:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type amplitude\n", meas_ptr->meas_index);
			break;
			
		case EYE_PCROSS:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type pcross\n", meas_ptr->meas_index);
			break;
			
		case EYE_NCROSS:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type ncross\n", meas_ptr->meas_index);
			break;
			
		case EYE_EXTICTRATIO:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type extinctratio\n", meas_ptr->meas_index);
			break;
			
		case EYE_QFACTOR:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type qfactor\n", meas_ptr->meas_index);
			break;
			
		case EYE_AOPTPWRDBM:
			str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:type aoptpwrdbm\n", meas_ptr->meas_index);
			break;
			
		default:
			return CMD_ERROR;
	}

	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int meas_entry_init(meas_entry_t *meas_ptr, const int index, const int type)
{
    meas_ptr->meas_index = index;
	meas_ptr->meas_type = type;
	meas_ptr->meas_value = 0;
	INIT_LIST_HEAD(&meas_ptr->list);

	return CMD_SUCCESS;
}

/*
measurement:measx:type?
int get_measurement_measx_type(int *type_ptr)
{
	return CMD_SUCCESS;
}
*/

//meas->meas x->measurement value
int get_measurement_meax_value(ViSession *vi, meas_entry_t *meas_ptr, const int index)
{
    int str_len = 0;
    double value = 0.0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;
	
	str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:value?\n", index);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;	
	viPrintf(*vi, cmd_str);
	viScanf(*vi, "%lf", value);
    meas_ptr->meas_value = value;
	viUnlock(*vi);

	return CMD_SUCCESS;
}

int set_measurement_select_meas(ViSession *vi, meas_config_t *meas_config, const int measx, const char *type)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    if (type == NULL)
        return CMD_ERROR;
    str_len = snprintf(cmd_str, CMD_STR_MAX, "MEASUREMENT:MEAS%d:TYPE %s\n", measx, type);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int set_measurement_measx_sourcetype(ViSession *vi, meas_config_t *meas_config, const int measx, const int source, const char *type)
{
    int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    if (type == NULL)
        return CMD_ERROR;
    str_len = snprintf(cmd_str, CMD_STR_MAX, "measurement:meas%d:source%d:wfmdb:sigtype %s\n", measx, source, type);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

int set_measurement_readout(ViSession *vi, int state)
{
	int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "display:measreadout %d\n", state);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

//waveform database
int set_wfmdbx_display(ViSession *vi, const int index, const int state)
{
	int	str_len = 0;
    char cmd_str[CMD_STR_MAX] = {0};
    ViStatus status = 0;

    str_len = snprintf(cmd_str, CMD_STR_MAX, "WFMDB:WFMDB%d:DISPlay %d\n", index, state);
    if (str_len == 0)
        return CMD_ERROR;

    status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
    if (status != VI_SUCCESS)
        return CMD_ERROR;
    viPrintf(*vi, cmd_str);
    viUnlock(*vi);

    return CMD_SUCCESS;
}

//hardcopy
int set_hardcopy_format(ViSession *vi, meas_config_t *meas_config, char *format)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "hardcopy:format %s\n", format);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	snprintf(meas_config->hardcopy_fmt, SHT_STR_MAX, format);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}

int csa8k_hardcopy(ViSession *vi, char *name)
{
	int	str_len = 0;
	char	cmd_str[CMD_STR_MAX] = {0};
	ViStatus	status = 0;

	str_len = snprintf(cmd_str, CMD_STR_MAX, "hardcopy:filename %s\n", name);
	if (str_len == 0)
		return CMD_ERROR;
	
	status = viLock(*vi, VI_EXCLUSIVE_LOCK, 2000, VI_NULL, VI_NULL);
	if (status != VI_SUCCESS)
		return CMD_ERROR;
	viPrintf(*vi, cmd_str);
	viUnlock(*vi);
	
	return CMD_SUCCESS;
}
