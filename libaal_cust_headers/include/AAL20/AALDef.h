#ifndef __AAL_DEF_H__
#define __AAL_DEF_H__

#define DRE_POINT_NUM 29
#define DRE30_BLK_NUM_MAX 16
#define DRE30_BLK_SFLT_SIZE_MAX 7

#define DRE30_17_BIN_MODE
#ifdef DRE30_17_BIN_MODE
#define DRE30_LUMA_POINT_BIT    4 // For ( 17 = 2^4 + 1 ) points
#else
#define DRE30_LUMA_POINT_BIT    5 // For ( 33 = 2^5 + 1 ) points
#endif

#define DRE30_LUMA_HIST_NUM           ( 1 << ( DRE30_LUMA_POINT_BIT ) )
#define DRE30_LUMA_HIST_NUM_WEIGHT    ( DRE30_LUMA_HIST_NUM + 1 )
#define DRE30_LUMA_CURVE_NUM          ( DRE30_LUMA_HIST_NUM + 1 )
#define Early_Term

#define DRE_VERSION_3_0   0
#define DRE_VERSION_3_1   1
//#define DRE_VERSION_3_5   2

/*
3.1 = 3.0 + 3 color + Gloal Y Hist
3.5 = 3.0 + 3 color + bilateral
*/
#define DRE_VERSION_6885
#ifdef DRE_ANDROID_PLATFORM
  #ifdef DRE_VERSION_6771

  #elif DRE_VERSION_6779
    #define DRE_VERSION DRE_VERSION_3_0
  #elif DRE_VERSION_6785
    #define DRE_VERSION DRE_VERSION_3_0
  #elif DRE_VERSION_6883
    #define DRE_VERSION DRE_VERSION_3_1
  #elif DRE_VERSION_6885
    #define DRE_VERSION DRE_VERSION_3_1
  #endif

#else
    #define DRE_VERSION DRE_VERSION_3_1
#endif

#define TBL_SIZE 20

enum DebugFlags {
    eDebugDisabled          = 0x0,
    eDebugInput             = 0x1,
    eDebugOutput            = 0x2,
    eDebugTime              = 0x4,
    eDebugContent           = 0x8,
    eDebugLABC              = 0x10,
    eDebugCABC              = 0x20,
    eDebugDRE               = 0x40,
    eDebugFilter            = 0x80,
    eDebugGame              = 0x90,
    eDebugPartial           = 0x100,
    eDebugBasic             = 0x200,
    eDebugAll               = 0x3FF
};

// Event bits
enum AALEvent {
    // Ambilient light changed
    eEvtALI             = 0x1,
    // Screen state changed. See ScreenState
    eEvtScrState        = 0x2,
    // User setting changed. See AALFunction
    eEvtUserSetting     = 0x4,
    eEvtFunction        = eEvtUserSetting,
    // User brightness configuration changed.
    eEvtUserBrightness  = 0x8,
    // Target backlight value changed
    eEvtTargetBacklight = 0x10,
    // Animation target changed
    eEvtLongTermBacklight = 0x20,
    // Configuration changed
    eEvtConfigChanged   = 0x40,
    // Some configuration field has been written
    eEvtFieldWritten    = 0x80,
    // Triggered by algorithm implementation
    eEvtActiveTrigger   = 0x100,
    // Intialize, set when boot or AAL restart
    eEvtInit            = 0x200,
    // FPS changed
    eEvtFPS             = 0x400,
    // Partial update, set when display request partial update
    eEvtPartialUpdate   = 0x800,
    // Some configuration field has been read
    eEvtFieldRead    = 0x1000,
};

enum AALFunction {
    eFuncNone   = 0,
    eFuncLABC   = 0x1,
    eFuncCABC   = 0x2,
    eFuncDRE    = 0x4,
    eFuncAPPGAMEPQ = 0x8
};

// The value should be the same as the SCREEN_STATE enum in IAALService
enum ScreenState {
    eScrStateOff = 0,
    eScrStateDoze = 1,
    eScrStateDim = 2,
    eScrStateOn = 3,
};

//enum DebugFlags {
//    eDebugDisabled          = 0x0,
//    eDebugInput             = 0x1,
//    eDebugOutput            = 0x2,
//    eDebugTime              = 0x4,
//    eDebugContent           = 0x8,
//    eDebugLABC              = 0x10,
//    eDebugCABC              = 0x20,
//    eDebugDRE               = 0x40,
//    eDebugFilter            = 0x80,
//    eDebugPartial           = 0x100,
//    eDebugAll               = 0x1FF
//};

enum AALRefreshLatency {
    eRefresh_17ms = 17,
    eRefresh_33ms = 33
};


struct AALInitParam {
    // Screen width & height
    int width;
    int height;
};

struct AALInitReg {
    // DRE
    int dre_map_bypass;
    // CABC
    int cabc_gainlmt[33];

    int dre_s_lower;
    int dre_s_upper;
    int dre_y_lower;
    int dre_y_upper;
    int dre_h_lower;
    int dre_h_upper;
    int dre_h_slope;
    int dre_s_slope;
    int dre_y_slope;
    int dre_x_alpha_base;
    int dre_x_alpha_shift_bit;
    int dre_y_alpha_base;
    int dre_y_alpha_shift_bit;
    int act_win_x_start;
    int act_win_x_end;

    int dre_blk_x_num;
    int dre_blk_y_num;
    int dre_blk_height;
    int dre_blk_width;
    int dre_blk_area;
    int dre_blk_area_min;
    int hist_bin_type;
    int dre_flat_length_slope;

//#ifdef DRE_VERSION_6885     // use DMDP as DISP


    int dre_bitplus_contour_range_th;
    int dre_bitplus_contour_range_slope;
    int dre_bitplus_diff_count_th;
    int dre_bitplus_diff_count_slope;
    int dre_bitplus_pxl_diff_th;
    int dre_bitplus_pxl_diff_slope;
    int dre_bitplus_noise_range_th;
    int dre_bitplus_noise_range_slope;
    int dre_bitplus_signchange_count_th;
    int dre_bitplus_signchange_count_slope;
    int dre_bitplus_high_lvl_out_oft;
    int dre_bitplus_high_lvl_pxl_slope;
    int dre_bitplus_high_lvl_pxl_th;
    int dre_bitplus_high_lvl_out_oft2;
    int dre_bitplus_high_lvl_pxl_slope2;
    int dre_bitplus_high_lvl_pxl_th2;
    int dre_bitplus_to_ali_wgt;
    int dre_pxl_diff_th_for_flat_pxl;
    int dre_pxl_diff_slope_for_flat_pxl;
    int dre_pxl_diff_th;
    int dre_pxl_diff_slope;
    int dre_flat_length_th;
    // tile
    int HSIZE;
    int VSIZE;


    int act_win_y_start;
    int act_win_y_end;

    int blk_num_x_start;
    int blk_num_x_end;
    int blk_cnt_x_start;
    int blk_cnt_x_end;
    int blk_num_y_start;
    int blk_num_y_end;
    int blk_cnt_y_start;
    int blk_cnt_y_end;

    int last_tile_x_flag;
    int last_tile_y_flag;


    //note demo window
    int win_x_start;
    int win_x_end;
    int win_y_start;
    int win_y_end;
    int split_en;
    int split_swap;

    int dre_s_lower2;
    int dre_s_upper2;
    int dre_y_lower2;
    int dre_y_upper2;
    int dre_h_lower2;
    int dre_h_upper2;
    int dre_h_slope2;
    int dre_s_slope2;
    int dre_y_slope2;
    int dre_s_lower3;
    int dre_s_upper3;
    int dre_y_lower3;
    int dre_y_upper3;
    int dre_h_lower3;
    int dre_h_upper3;
    int dre_h_slope3;
    int dre_s_slope3;
    int dre_y_slope3;


    int save_first_blk_col_flag;
    int save_last_blk_col_flag ;
    int round_to_9b;
    int y2r_en;
    int r2y_en;

    int dre0_blk_num_x_start;
    int dre0_blk_num_x_end;
    int dre1_blk_num_x_start;
    int dre1_blk_num_x_end;
//#endif

};
#pragma pack(1)
// Game PQ FW registers
struct AALGPQReg {

    int dre_fw_en;
    int dre_curve_en;
    int dre_gain_flt_en;
    int bADLWeight1;
    int bADLWeight2;
    int bADLWeight3;
    int bBSDCGain;
    int bBSACGain;
    int bBSLevel;
    int bMIDDCGain;
    int bMIDACGain;
    int bWSDCGain;
    int bWSACGain;
    int bWSLevel;
    int dre_dync_spike_wgt_min;
    int dre_dync_spike_wgt_max;
    int dre_dync_spike_th;
    int dre_dync_spike_slope;
    int bSpikeBlendmethod;
    int bSkinWgtSlope;
    int bSkinBlendmethod;
    int SkinDummy1;
    int Layer0_Ratio;
    int Layer1_Ratio;
    int Layer2_Ratio;
    int Dark_Ratio;
    int Bright_Ratio;
    int dre_dync_flt_coef_min;
    int dre_dync_flt_coef_max;
    int dre_dync_flt_ovr_pxl_th;
    int dre_dync_flt_ovr_pxl_slope;
    int dre_iir_force_range;
    int LLPValue;
    int LLPRatio;
    int APLCompRatioLow;
    int APLCompRatioHigh;
    int FltConfSlope;
    int FltConfTh;
    int BlkHistCountRatio;
    int BinIdxDiffSlope;
    int BinIdxDiffTh;
    int BinIdxDiffWgtOft;
    int APLTh;
    int APLSlope;
    int APLWgtOft;
    int APL2Th;
    int APL2Slope;
    int APL2WgtOft;
    int APL2WgtMax;
    int BlkSpaFltEn;
    int BlkSpaFltType;
    int LoadBlkCurveEn;
    int SaveBlkCurveEn;
    int Flat_Length_Th_Base;
    int Flat_Length_Slope_Base;
    int DZ_Fallback_En;
    int DZ_Size_Th;
    int DZ_Size_Slope;

#if ((DRE_VERSION == DRE_VERSION_3_1) )
    int bGreenWgtSlope;
    int dre_dync_compact_wgt_min;
    int dre_dync_compact_wgt_max;
    int dre_dync_compact_th;
    int dre_dync_compact_slope;
    int bCompactBlendmethod;
    int dre_dync_compact_LowBoundBin;
    int dre_dync_compact_HighBoundBin;
    int dre_dync_compact_BinMinWeight;
    int dre_dync_compact_BinMaxWeight;
    int dre_dync_flt_coef_increase;//30 new
    int flatblknum_ratio;
    int bColorWgtSlope;//
    int bColorBlendmethod;//
    int ColorDummy1;//

#else
    int RSV00;
    int RSV01;
    int RSV02;
    int RSV03;
    int RSV04;
    int RSV05;
    int RSV06;
    int RSV07;
    int RSV08;
    int RSV09;
    int dre_dync_flt_coef_increase;//30 new
    int flatblknum_ratio;
    int RSV10;//
    int RSV11;//
    int RSV12;//

#endif
    int reservedArray[327];
};
struct GamePQCustXMLBuf
{
    unsigned int Size;//Byte
    AALGPQReg iDRERegEntry;
    unsigned int CheckCode;
    unsigned int checksum;
};
#pragma pack()

// Game PQ Read only registers
struct AALGPQReg_RO
{
    int g_hist_set01;
    int g_hist_set02;
    int g_hist_set03;
    int g_hist_set04;
    int g_hist_set05;
    int g_hist_set06;
    int g_hist_set07;
    int g_hist_set08;
    int g_hist_set09;
    int g_hist_set10;
    int g_hist_set11;
    int g_hist_set12;
    int g_hist_set13;
    int g_hist_set14;
    int g_hist_set15;
    int g_hist_set16;
    int g_hist_set17;
    int g_curve_set01;
    int g_curve_set02;
    int g_curve_set03;
    int g_curve_set04;
    int g_curve_set05;
    int g_curve_set06;
    int g_curve_set07;
    int g_curve_set08;
    int g_curve_set09;
    int g_curve_set10;
    int g_curve_set11;
    int g_curve_set12;
    int g_curve_set13;
    int g_curve_set14;
    int g_curve_set15;
    int g_curve_set16;
    int g_curve_set17;
};

// Fields collected from AAL HW
struct AALInput {
    // Please check the event by
    // if (eventFlags & eEvtALI) { ... }
    unsigned int eventFlags;

    // Calibrated value(LUX) from light sensor
    // < 0 means invalid yet
    int currALI;

    // Test by
    // if (funcFlags & eLABC) { ... }
    // Manual mode = 0x0
    // Auto mode = LABC + CABC + DRE = (eLABC | eCABC | eDRE) = 0x7
    // ECO mode = CABC only = eCABC = 0x2
    //
    // To know which function is toggled, we can use XOR to test
    // ((prevFuncFlags ^ funcFlags) & eLABC)
    unsigned int prevFuncFlags;
    unsigned int funcFlags;

    bool prevIsPartialUpdate;
    bool isPartialUpdate;

    ScreenState prevScrState;
    ScreenState currScrState;

    // Target backlight of Android calculated or user set.
    // This will be used on the moment of user setting changed or mode changed.
    // AAL should smooth the backlight to the target before give up the control.
    // [0, 1023] -> [0, 4095] (12-bit)
    unsigned int targetBacklight;

    // The destination backlight of manual mode, usually the position of the
    // backlight scroll bar position.
    // [0, 1023]
    unsigned int longTermBacklight;

    /*
     * The brightness level of LABC configured by user.
     * [0, 255]
     */
    int userBrightnessLevel;

    // List the registers should be read from HW
    int MaxHisBin[33];        // 25-bit

    // List the Y hist. read from HW
    int YHisBin[33];        // ? -bit
    // Mainly for the statistics of skin-tone pixels
    int ColorHist;

    // Block Histogram
    int DREMaxHisSet[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX][DRE30_LUMA_HIST_NUM_WEIGHT];

    // Block APL
    int DRERGBMaxSum[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];

    // Block Chroma Confidence
    int DREChromaHist[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];
    int DREChromaHist2[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];
    // Block Flat Line Confidence
    int DREFlatLineCountSet[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];

    // Block Large Diff Confidence
    int DRELargeDiffCountSet[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];

    // Block Max Diff
    int DREMaxDiffSet[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX];

    // Block Numbers
    int dre_blk_x_num;
    int dre_blk_y_num;

    int PreFloatCurve[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX][DRE30_LUMA_CURVE_NUM]; // 15-bit [0, 255*128]
};

// Fields which will be set to HW registers
struct AALOutput {
    // List the register values should be set to HW

    // DRE
    int DREGainFltStatus[ DRE_POINT_NUM ];

    // Block Mapping Curve
    int DRECurveSet[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX][DRE30_LUMA_CURVE_NUM];

    int CurFloatCurve[DRE30_BLK_NUM_MAX][DRE30_BLK_NUM_MAX][DRE30_LUMA_CURVE_NUM];
    //CABC
    int cabc_fltgain_force;   // 10-bit; [0,1023]
    int cabc_gainlmt[33];

    int FinalBacklight;         // 10-bit; [0,1023]

    // To set new latency, please always get the minimum. For example,
    // output->refreshLatency = min(output->refreshLatency, newLatency);
    AALRefreshLatency refreshLatency;

    // Trigger main function next time anyway, regardless there is any event.
    // Set to true if output is not stable yet.
    bool activeTrigger;
    bool dre_frm_trigger;

    // flag for notify display that AAL accept partial update request or not
    bool allowPartialUpdate;
};

struct ImplParameters {
    int brightnessLevel;
    int darkeningSpeedLevel;
    int brighteningSpeedLevel;
    int smartBacklightStrength;
    int smartBacklightRange;
    int readabilityLevel;
    int readabilityBLILevel;
};

// Fields for DMDP dual pipe
struct DualInfoAAL {
    int MaxHis_denominator_pipe0[DRE30_BLK_NUM_MAX];
    int MaxHis_denominator_pipe1[DRE30_BLK_NUM_MAX];
};


struct AALDualInfo {
    // Dual mode info
    AALInitParam initParam;
    DualInfoAAL pipeinfo;
    int cuttingposition;
    int m_Pipe_num;
};


#endif
