#ifndef AALIMPLINTERFACE_H
#define AALIMPLINTERFACE_H
#include "AALCust.h"
#include "AALDef.h"
#include "PQSharedData.h"

#undef LOG_TAG
#define LOG_TAG "AAL"

class CAALFW;



enum LCM_TYPE {
    LCD = 0,
    AMOLED = 1
};

enum UD_CURVE_TYPE {
    PIXEL_GAIN = 0,
    BACKLIGHT_LEVEL = 1
};

enum FW_DRE_TYPE {
    FW_DRE_AAL = 0,
    FW_DRE_GAMEPQ = 1,
    FW_DRE_APPGAMEPQ = 2
};

struct AALInfo {
    int lcm_type;
    bool ess_ready;
    bool dre_ready;
    bool appgamepq20_ready;
    float ess_version;
    float dre_version;
};

#define IS_FIELD_LEGAL(f, s) (f > sizeof(s) - sizeof(uint32_t) || (f & 0x3) != 0)

class AALInterface {
public:
    AALInterface();
    ~AALInterface();

    int setESS_CurveType(int key);
    int setESS_PanelType(int key);
    int setESS_HistType(int key);
    int setSmartBacklightStrength(int level);
    int setSmartBacklightRange(int level);
    int setESSRegByVer(int level);
    int setDRERegByVer(int level);
    int setReadabilityLevel(int level);
    int setReadabilityBLILevel(int level);
    void getParameters(ImplParameters *outParam);
    void setUDCurve(int type, int index, int level);
    int setTuningReg(char *reg_name, int *value);
    int getTuningReg(char *reg_name, int *value);
    int setBL_SmoothType(int key);
    void combineDispDualPipeInput(AALInput & pipe0, AALInput & pipe1, AALInput &full, const AALInitParam &initParam);
    void DualPipeDISPBlockStatistics(AALInput & pipe0, AALInput & pipe1, AALInput & full, const AALInitParam &initParam, const DualInfoAAL &pipeinfo, const int cuttingposition);
    void readField(uint32_t field, uint32_t *value, int dreType = FW_DRE_AAL);
    void writeField(uint32_t field, uint32_t value, int dreType = FW_DRE_AAL);
    bool isFieldLegal(uint32_t field, int dreType = FW_DRE_AAL);

    bool isAALFwBypassed();

    void onCalculate(AALInput &input, AALOutput *output, int dreType); // single-pipe
    void onCalculate(AALInput &pipe0, AALInput &pipe1, AALOutput *output, AALDualInfo& mDualInfo, int dreType); // dual-pipe
    void onCalculate(AALInput &input, AALOutput *output, uint32_t* eglvalue, int egl_ver, int egl_size); // single-pipe for APPGamePQ
    void onCalculate(AALInput &pipe0, AALInput &pipe1, AALOutput *output, AALDualInfo& mDualInfo, uint32_t* eglvalue, int egl_ver, int egl_size); // dual-pipe for APPGamePQ
    void functionCheck();
#ifdef MTK_AAL_NEED_LICENSE
    bool licenseIsValid();
#endif
    void onInitFunction();
    void onInitCommon(const AALInitParam &initParam, AALInitReg *initReg, int dreType = FW_DRE_AAL, bool isDualPipe = false);
    void onInitPlatformFunc(const AALInitParam &initParam, CustParameters &cust, AALInitReg *initReg, int dreType = FW_DRE_AAL);
    void onInitPlatform(const AALInitParam &initParam, CustParameters &cust, AALInitReg *initReg, int dreType = FW_DRE_AAL);
    void onSelectTable(int sel, int dreType, bool tuningMode);
    void onSwitchDREFunc(AALInitParam &initParam, AALInitReg *initReg, AALOutput *output, int newDreType);
    bool loadGameDRETable(CustParameters &cust);
    void setDebugFlags(unsigned int debug);
    void getAALInfo(struct AALInfo *aalinfo);
    void onLoadXML(unsigned char* setting);
    void onLoadGamePQXML(unsigned char* setting);
    int SetPQAlgSharedData(class PQAlgSharedData *pqalg_data);

private:
    CAALFW *mAALFW;
    int mSelTable;
    AALInput dualPipeInput;
    /* shared data between libpq/libaal */
    class PQAlgSharedData *pq_shared_data;
};


#endif

