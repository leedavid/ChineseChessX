#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include "movelist.h"
#include "piece.h"
#include "square.h"

static const quint8 _stox[90] = {
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,

	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
	0,    1,    2,    3,    4,    5,    6,    7,    8,
};

static const quint8 _stoy[90] = {
	0,    0,    0,    0,    0,    0,    0,    0,    0,
	1,    1,    1,    1,    1,    1,    1,    1,    1,
	2,    2,    2,    2,    2,    2,    2,    2,    2,
	3,    3,    3,    3,    3,    3,    3,    3,    3,
	4,    4,    4,    4,    4,    4,    4,    4,    4,

	5,    5,    5,    5,    5,    5,    5,    5,    5,
	6,    6,    6,    6,    6,    6,    6,    6,    6,
	7,    7,    7,    7,    7,    7,    7,    7,    7,
	8,    8,    8,    8,    8,    8,    8,    8,    8,
	9,    9,    9,    9,    9,    9,    9,    9,    9,
};

#define XMM_ALIGN __declspec(align(16))
#include <intrin.h>
#define Bitboard __m128i

#define TRUE   1
#define FALSE  0

#define StoY(s) (_stoy[s])       
#define StoX(s) (_stox[s])       
#define XYtoS(x,y)  (Square((y)*9+(x)))


static const quint64 CHE_Mult_R[90] =
{
	0x2040220240280201,0x1020004C20850002,0x01040C0901001800,0x0D010695152100A3,0x0204026045003010,0x2040504200653310,
	0x2408059034405A74,0x08200A694A152002,0x01011A480B062810,0x1008100001580D00,0x00F4102046892511,0x04F20C10062004A3,
	0x181010500B450230,0x583C088801D30942,0x0920450040114A70,0x0982028200001841,0x19040A2040421013,0x0408100A56A21010,
	0x2400004016004020,0x6B240102080B0080,0x44000B430B800B01,0x000064D008056524,0x4020008539A02902,0x702619100C2310C0,
	0x010802040A922158,0x0DA0144101200008,0x21C8244060C00A3C,0x0020042060204040,0x5289000141040C02,0x240220A020300B35,
	0x04800330203110A2,0x0099325810094120,0x28087808114B0A55,0x231106DA10192055,0x1400480860814118,0x3104205020150B26,
	0x2001540002040149,0x0824040401102078,0x6033200011580608,0x7754107232042084,0x2048400440102000,0x010010204B020100,
	0x1843111040230460,0x1A140926408A2444,0x0012182A00100740,0x44F410D000800804,0x614868A000410208,0x210C0C0410A00810,
	0x242A020001410203,0x20200D007004080D,0x28441340420C2046,0x060014024022050A,0x10C100180900102E,0x104910002B601808,
	0x041A120801710281,0x42080000143A3041,0x22A1160420C80883,0x56D20182104B4881,0x4062610400280081,0x002C3082082464E2,
	0x4058100400063881,0x02946C0244451341,0x0804688C03391081,0x40802C0B720046A0,0x2207140A74002424,0x20C0222700006960,
	0x0408123606B10203,0x2021164141300818,0x02401045740C0020,0x0460690809192411,0x410408500A811C02,0x120200C000140809,
	0x112040190D080200,0x080E1027100E0065,0x010204000A410831,0x070810A041410030,0x0064080406180700,0x7001020120510028,
	0x3F01020620801420,0x4016502008000885,0x4C10201000003045,0x6701102010502844,0x0268061000404C04,0x0102203003890290,
	0x0442302024480401,0x0D08481002A102E0,0x0840604408500B45,0x1001542011801A1B,0x4100104040C40247,0x08400B0203904001,
};

static const quint64 CHE_Mult_F[90] =
{
	0x3450044242820011,0x0808100210510138,0x0090008110404860,0x4804460005001004,0x6202003152020C20,0x2A01088008080110,
	0x0180480114281004,0x010018301A882104,0x3820200A09811412,0x22580E0800441085,0x0C10008024151006,0x5410030400194041,
	0x2080420811841211,0x08902A800C8108A0,0x00520C8904121310,0x2102403927011004,0x52B11010201A01A2,0x5460041054062042,
	0x22AE112060810121,0x1022408800414084,0x2448020400980A6C,0x1001061805001401,0x008301C0123E0A02,0x03020043140F3141,
	0x3A040440080940B8,0x15014180124A0141,0x1B02062203102809,0x092003171D513041,0x6C3C0024007111A0,0x6A0308004C106212,
	0x2428004C50022042,0x500C410800512804,0x02C3001205482610,0x3200100208202021,0x0080084003002102,0x602A02100802141A,
	0x2804008400222235,0x2001002106311900,0x2004103408241101,0x081100E044044A28,0x0A02202043001020,0x584218C240040450,
	0x04310060011334E9,0x044940C40070002C,0x108142C404040036,0x100510D028806081,0x10420092584C0860,0x208C042042002964,
	0x0168088005C00114,0x504010A020E20050,0x0A01106001042A08,0x1A4300A041010C05,0x10084009028020C4,0x44CC04D02108250A,
	0x0F30012038721451,0x0244002604001024,0x0890404008820448,0x2002406205F04401,0x00C2002804094048,0x48032060090800A0,
	0x4101010444207E04,0x402C084242830410,0x0180142038470260,0x0242020052000831,0x01600B8050840888,0x0430208010811004,
	0x3784302220140101,0x0B42000850801234,0x0902014008012042,0x40923C080D0B1048,0x2039200A06890952,0x25821408101B2181,
	0x0044184A2400080D,0x1420014500222102,0x4288401041941480,0x0170280901001112,0x0A101023400121A0,0x0208040450200107,
	0x2010101040014812,0x2B4005501050008E,0x10040B0110220602,0x0010250101E20055,0x0820060023001122,0x0D080104002408C8,
	0x0A04021200082108,0x06C4002460A00A06,0x3E80104001600C10,0x1821000104180049,0x63C0041410002801,0x19802105020206C2,
};

static const  quint64 PAO_EAT_Mult_R[90] =
{  //7位
	0x4810085B72032000,0x582028000082299A,0x0102030C19001220,0x4187021022402D90,0x1020281D31340014,0x22040303060C609C,
	0x0101298803820409,0x18403C0000B20278,0x408020032B000D50,0x1910200C44952004,0x4044100C05880006,0x408204000002021B,
	0x0108104431800202,0x2008080818E32082,0x0C1404824B026850,0x246C2000313C4CB0,0x229103020940068A,0x2320407002424140,
	0x258020C0400E4003,0x094304100A381200,0x4741220404000B64,0x0003080810881880,0x092602042088128C,0x08D80C09060A4008,
	0x0404102018C0244C,0x0B19451142912782,0x7000040800B22900,0x0301012420194A21,0x10C40000101B0208,0x70820012040A0004,
	0x4C18244214836201,0x401000B022110106,0x05330C0022016A24,0x03060A40204C0022,0x32C840C820200206,0x40130820200B6800,
	0x3102010850810028,0x4508217062060808,0x588E111121810460,0x0000142205020004,0x00094B0001020108,0x0080020002102089,
	0x3412520001271228,0x0FC4101205040088,0x2000002C10301E18,0x0880083704100808,0x60A0001508C14820,0x3061490A09080828,
	0x601024631A010201,0x7632050200060444,0x0540108000020481,0x4800200821080810,0x002A3F2004806124,0x4890001820044810,
	0x1081004015240081,0x00C825102C200141,0x7E99420640000D81,0x088100840203004D,0x202003C122000081,0x090111A214000081,
	0x42004308210B2881,0x0140481024491081,0x201000231C001102,0x0C08031135440914,0x481F1C2110022028,0x06030185200C4081,
	0x2148246808000008,0x040800643C040550,0x0232400814442004,0x40940891230467CA,0x5020075240011802,0x0202628110414083,
	0x1381013A0009182D,0x34010161104C4004,0x0008100C0CC20010,0x50604187301206C2,0x0090200104234485,0x604604624C506C00,
	0x50205580620807C4,0x40A04104005029C0,0x1D08100201004108,0x0084140800600AC0,0x2611098200C61080,0x0900020404484160,
	0x4071102010230518,0x0252081004007012,0x01E0009020246615,0x01A042B047615324,0x2700204064000082,0x0080040801000201,
};

static const quint64 PAO_EAT_Mult_F[90] =
{ //8位
	0x0A60058107001B11,0x6190008800800830,0x4C1002034A286004,0x0A44005260200440,0x24002300201810A0,0x0623404A40100710,
	0x1AA830400B041C08,0x0080084003922502,0x248410300900400A,0x01CA040121830211,0x21010B8305002100,0x400145810140090E,
	0x4306010204107A48,0x1830120140120182,0x1E34008031041054,0x4109088004180883,0x0E0C3C2101824847,0x00801688144F5282,
	0x0C0300E854E30211,0x1102041400820194,0x2000408830450024,0x0382418441EC0142,0x02CA0200436658A0,0x742240424002006B,
	0x0903280A390150C4,0x1103609801003284,0x218C41000AC20401,0x08010A9010D22901,0x217D0A0604002020,0x361005821C851012,
	0x020800141C200331,0x0900620870211120,0x45C14080691010B0,0x011A060640D02628,0x3B0C1042118150D4,0x0008480860841202,
	0x2A0A1C0020426289,0x2C20454300020040,0x2200504C08DB2022,0x2004081420331082,0x0114000852124608,0x10F8500501232169,
	0x1011000402E34242,0x010262084640201C,0x0004203C01042122,0x27E000D22415441F,0x04200400128A1990,0x1010488200100150,
	0x00820200202301A2,0x4606406510820058,0x0285200250032442,0x0A80590102020024,0x19040D0200502001,0x4E14046520480043,
	0x009828C124041891,0x0881052010B20440,0x6810002240900282,0x08101044081E4020,0x2189051820404418,0x2804512401200189,
	0x0224040802041101,0x0C25030808080012,0x4804240114A802A0,0x180150B200A02460,0x0010010110162078,0x2305080638481440,
	0x3688210308080628,0x0C20401448064010,0x0387311024107010,0x5286021010010104,0x18061640031A0022,0x1020420063852041,
	0x001030C020A03221,0x42A00C0400604002,0x20B9406108081480,0x6A28220040406440,0x22012088103004D4,0x22C7000418380041,
	0x220A038021280145,0x0C08101408104236,0x0822101110440242,0x0408080744042005,0x4005090801004052,0x2810006044944014,
	0x2020404040800130,0x2623008900082230,0x3201400819651010,0x1301002200D20081,0x4004104000840842,0x400448100400440A,
};

static const quint64   PAO_SUPER_Mult_R[90] = {
	0x0502000100480400,0x0282000812200228,0x00C4024419862021,0x203C460901FC480D,0x408810401C941810,0x02042C3306005008,
	0x2102002400400A00,0x620805023240606A,0x20402A8622102B0A,0x40102011601C4812,0x1330309000185447,0x018020B809A65820,
	0x04081021100000F8,0x229811082C011005,0x00A204944D210024,0x081023004C0210A5,0x0081040A00811088,0x12081000031D4131,
	0x4C24640805000045,0x1884128403002340,0x0058041801200100,0x245C204105831000,0x150404084A052404,0x0C80204505254811,
	0x10200102020012C0,0x100204C305005682,0x180100C040541600,0x2001200E04054000,0x1F0F500942010980,0x700A52420A262024,
	0x4028510404007164,0x2C83280204202604,0x4012402024441880,0x112059B210281000,0x01020C840C005888,0x400A143102010000,
	0x1008102B42040014,0x0018440601140820,0x48400A34340808B9,0x00A826851B820D67,0x1548100054081000,0x0408286040811D20,
	0x30011292006102A2,0x00084002410408A2,0x2300090D30100800,0x150402C11A110200,0x3320005160C94103,0x1300022210000410,
	0x0A50048100380808,0x0809600204200890,0x4000602029590202,0x3100210040041014,0x4834041700014504,0x43B0238202210204,
	0x010068220C406581,0x08420B2510200141,0x02294210201021DB,0x3018408016042481,0x5414223006994881,0x024C2042250405B1,
	0x22800205421570C2,0x40002E981C010441,0x40072C0040020D02,0x4080058804A14312,0x2061500011044440,0x2040120308D41206,
	0x02080C2001002140,0x0408220001801B14,0x0220009041190B01,0x22AC200155000644,0x2080682A36D00188,0x04080E0560831008,
	0x00502008705A412C,0x0224710808320130,0x2A80622030002402,0x0401052D00AB3604,0x0503064200080211,0x0290204121611423,
	0x1484029611840284,0x2612080448954093,0x0406040000AB5822,0x4443102009101037,0x00001A186100300C,0x08F2040800285000,
	0x050612041400086F,0x04850081018C51C7,0x5224081000350C82,0x0203409429884240,0x0C89040E20102023,0x001D081004232950,
};

static const quint64  PAO_SUPER_Mult_F[90] = {
	0x000A060201110301,0x1002092604010054,0x0410010024802262,0x1442005600800C04,0x1012016014190801,0x1100080508112008,
	0x0880548024180084,0x050050012864083C,0x080A080B014E0401,0x1102011101900B49,0x01541148009F00C8,0x3009041601C1000A,
	0x0040540020204310,0x6802528A14851460,0x4084204802480E50,0x6520308001204A87,0x5870400315380A84,0x2B51605002501116,
	0x3020200824622041,0x104016084A906180,0x3610011064101C73,0x1890003324C82058,0x010801311C202161,0x55140018220A1512,
	0x0A41025040010042,0x430100E001221383,0x012C440210AA0382,0x0488040E5F214A31,0x2028408102404820,0x0942044004330401,
	0x4C0641020A100B02,0x61A1501100341295,0x0B32508000B41090,0x0899301101295848,0x001220240C003012,0x1142412200002281,
	0x062051402A824041,0x1A6000481288481C,0x6410010009800852,0x620A02602A200110,0x24620200222700FA,0x1960244826020201,
	0x00E3100540084041,0x6020021001260904,0x40C04401002C3272,0x5808088402001007,0x0822020114201605,0x0128009422004050,
	0x529040404540001B,0x0943080900200150,0x01C2088008481844,0x2129009A040202A6,0x101111010C0400EE,0x1124012000B05041,
	0x28210224033A01C5,0x023E040150841004,0x2381402450103300,0x040E009020880100,0x2B08341140570827,0x31A3010015050090,
	0x0101182804842184,0x0A00036018021290,0x008020C230170120,0x1001238820940170,0x203402060029118C,0x4009008230050880,
	0x0AC805807C282015,0x4410080848870410,0x494301C130A20081,0x1084111040100042,0x6404211419014041,0x080060020540612A,
	0x0204110212130185,0x0850480644201004,0x6A08084750300228,0x1398680808100409,0x10061A5820022023,0x5030508008410182,
	0x010120010C071344,0x0500181305100813,0x008E080118420202,0x5288185400420009,0x1810100410820808,0x6850009020084038,
	0x4A02010901382240,0x24040090200D6306,0x18120004204A3202,0x296A080808200C04,0x000450060A8C0404,0x2C08680844440302,
};
static const quint64   Ma_to_King_Mult[90] ={
	0x41BC160003600464,0x11ED108B24084D0C,0x5664000802001380,0x2452186110900443,0x448A400C008054E4,0x421C5C0022014300,
	0x130429F0501440CC,0x02D04B00000A0823,0x144C6C7902641016,0x24A21CD20CE6018C,0x604B740840002884,0x2BB2412161002040,
	0x20CB0A2021034C03,0x08012A0B23421C1E,0x0CA2511872514028,0x590864815A860078,0x40016F22023E0000,0x100A6A6450311100,
	0x2449283D72184240,0x020A24A84C802148,0x343830C300000090,0x0004120C68200000,0x1002011029080942,0x05EB2A8410344000,
	0x143F012432690A02,0x580C7A2018E47D00,0x0200540B681400A0,0x1008182118CA4808,0x2040095704A40041,0x02010A8902130223,
	0x0323108245003448,0x24C810A110810080,0x0408031020922808,0x1890058013080840,0x0044003208496404,0x0240620708C40820,
	0x00444025042A5200,0x1182388846E30211,0x64040C521D032CAA,0x2418221500821C8B,0x0810020C58204120,0x2021006254C82095,
	0x0C32400160B023A0,0x0224287130265A4A,0x394009090A112111,0x106424C409E10087,0x148010E2045C6084,0x5251040314A04185,
	0x5110478415432540,0x10A8004112214462,0x0104601008426452,0x20912C4340084488,0x166005021068278C,0x27061900440823C5,
	0x62680689011A007D,0x2200501810385E86,0x221A2D4C40004B08,0x4535028523984022,0x0828008049017043,0x24900195304514B8,
	0x0E023200501810F7,0x367C4020249C040E,0x0A2429232801416C,0x3041660220010628,0x158A001208005180,0x1308340D2CA45080,
	0x0830006000992895,0x211424C816210348,0x148448864E087148,0x152A08380C024C3E,0x119113346001188A,0x021A380A12000A0D,
	0x103F608350800003,0x542A701440020000,0x2046480800662434,0x2105644302000412,0x05E204C0504D40E0,0x01E600A821040C0C,
	0x5889711400200000,0x40C738000801100B,0x539E60A510B10942,0x03950AA802092065,0x207302391A5A0010,0x00E8118C02140190,
	0x207002C941B80020,0x0088019230280444,0x0E2420C460680614,0x1588424C1970638C,0x008114E964423906,0x175051AE08A81510,
};
static const  quint64   King_to_Ma_Mult[90] = {  // 这个是错的,要改一下.
	0x423F718020C03018,0x10326380208146A2,0x095960002514022A,0x10B930A009455000,0x0856628408240488,0x54393284019068C2,
	0x10864C8879D85478,0x209033010803058E,0x18107F803F010022,0x4F7A0420580108C1,0x104608B011B00060,0x2228044100000A20,
	0x084821142B043934,0x02010112400A0CD2,0x12114048062440E0,0x00980E4002010000,0x4882491230104016,0x0856084A60060580,
	0x205E4DC848242410,0x4410020232801880,0x408442222054040E,0x1822420902806C00,0x02822AC040810227,0x0044481620B22344,
	0x45044903208262C0,0x0AB22003118403E8,0x388212003B4A0004,0x54A423981F1101E0,0x032451315218040A,0x02081084024401C1,
	0x3000144100884474,0x40220C44232220D7,0x5051528020464C58,0x04B3048C40902056,0x1884401170480460,0x334B4E6714061044,
	0x0840103618047862,0x63334002300C4081,0x0108013220004400,0x0000186220184304,0x0014033624B41043,0x0244402641010934,
	0x1B043088118A2202,0x03B0009022960422,0x01041082162B0A50,0x4800200F044020AF,0x5008084201115882,0x60022D721A452108,
	0x3061412108430222,0x6110048061113122,0x00034EB500225744,0x0A290030604926D4,0x0392220000226601,0x604050004A0B7615,
	0x6CC2224000014C90,0x1042541040023001,0x2076285000404A10,0x086424802C411120,0x08240312108C1280,0x112C02881A9C4812,
	0x010820E000830842,0x0C49006401156201,0x4B29404A04000258,0x425F6041018B1680,0x0120100241050319,0x0110400222410625,
	0x4051621820886C20,0x0412245951082A91,0x002C649825280928,0x06C232B223400144,0x010A4C001078021A,0x03005F0660000026,
	0x400B0FFC15802480,0x638A2C0328605305,0x4503082325014A8C,0x71402A140EE42C40,0x08A03D0B22330028,0x08A0610A338D4C41,
	0x0122068438090288,0x38881B1104491100,0x24D61DC860264220,0x08FF420002510181,0x0C32660800E511C0,0x0093288600215212,
	0x20B2601401705002,0x200632400EAC5074,0x0843190918604110,0x008B328220624468,0x044A666658805219,0x05657F6100420251,
};
static const quint64 XIANG_Mult[90] ={
	0x0000000000000000,0x0000000000000000,0x0846544220046044,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x060B320840800000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x1723562921205264,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x1C12041844F00A90,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x608148C405720201,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x4801441E30100006,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x244A504030846506,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x7442718222603859,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x6A286108113101D3,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x6035100620224020,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x4091200001411038,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x100035F04846028D,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,0x540C1C9101602040,
	0x0000000000000000,0x0000000000000000,0x0000000000000000,0x00430948100A1120,0x0000000000000000,0x0000000000000000,
};

static const quint64 XMM_ALIGN Rank0BB[2] = { 0x00000000000001ff, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank1BB[2] = { 0x000000000003fe00, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank2BB[2] = { 0x0000000007fc0000, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank3BB[2] = { 0x0000000ff8000000, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank4BB[2] = { 0x00001ff000000000, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank5BB[2] = { 0x003fe00000000000, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank6BB[2] = { 0x7fc0000000000000, 0x0000000000000000 };
static const quint64 XMM_ALIGN Rank7BB[2] = { 0x8000000000000000, 0x00000000000000ff };
static const quint64 XMM_ALIGN Rank8BB[2] = { 0x0000000000000000, 0x000000000001ff00 };
static const quint64 XMM_ALIGN Rank9BB[2] = { 0x0000000000000000, 0x0000000003fe0000 };
static const quint64 XMM_ALIGN File0BB[2] = { 0x8040201008040201, 0x0000000000020100 };
static const quint64 XMM_ALIGN File1BB[2] = { 0x0080402010080402, 0x0000000000040201 };
static const quint64 XMM_ALIGN File2BB[2] = { 0x0100804020100804, 0x0000000000080402 };
static const quint64 XMM_ALIGN File3BB[2] = { 0x0201008040201008, 0x0000000000100804 };
static const quint64 XMM_ALIGN File4BB[2] = { 0x0402010080402010, 0x0000000000201008 };
static const quint64 XMM_ALIGN File5BB[2] = { 0x0804020100804020, 0x0000000000402010 };
static const quint64 XMM_ALIGN File6BB[2] = { 0x1008040201008040, 0x0000000000804020 };
static const quint64 XMM_ALIGN File7BB[2] = { 0x2010080402010080, 0x0000000001008040 };
static const quint64 XMM_ALIGN File8BB[2] = { 0x4020100804020100, 0x0000000002010080 };

static const quint64 XMM_ALIGN RpawnOverBB[2] = { 0x00001fffffffffff,0x0000000000000000 };  //过河的红兵
static const quint64 XMM_ALIGN BpawnOverBB[2] = { 0xffffe00000000000,0x0000000003ffffff };  //过河的黑兵

static const quint64 XMM_ALIGN WHOLE_BITBOARD90[2] = { 0xffffffffffffffff,0x03ffffff };       //所有90格棋子

#define ALL_B90 _mm_load_si128((__m128i*)(WHOLE_BITBOARD90))

//static const quint64 XMM_ALIGN TiMenBit_Pawn[2] = { 0x0000000000a0d844,0x0000000000886c14 };

extern Bitboard OneRpawnOrRking_AttackBB[90];      // 红兵,红将,攻击其它的棋格.
extern Bitboard OneBpawnOrBking_AttackBB[90];      // 黑兵,黑将

extern Bitboard ShiAttackBB[90];                   // 双方的仕攻击到 90 的位棋盘

//extern Bitboard MaHouPaoByKing[90];                // 马后炮的位置

extern Bitboard Attack_By_Rpawn_Rking[90];         // 所有可攻击到棋格的红兵, 红将 //兵是单向的
extern Bitboard Attack_By_Bpawn_Bking[90];         // 所有可攻击到棋格的黑卒, 黑将

//extern Bitboard Ma_Pseudo_Good_Att[90];           // 马可能走到好步的位置.

extern Bitboard Ma_Pseudo_Att[90];                 // 马可能走到的所有位置

#define NUM_MA_TO_KING_ATT (1440)
extern Bitboard Ma_to_King_Mask[90];             // 从马的位置,来吃将, 是算一下别脚
extern Bitboard Ma_to_King_Attacks[NUM_MA_TO_KING_ATT];
extern int      Ma_to_King_AttackIndex[90];

#define NUM_KING_TO_MA_ATT (1440)
extern Bitboard King_to_Ma_Mask[90];             // 从将的位置,被马吃, 是算一下反别脚
extern Bitboard King_to_Ma_Attacks[NUM_MA_TO_KING_ATT];
extern int      King_to_Ma_AttackIndex[90];

//extern Bitboard fromtoBBback[90][90]; 
extern Bitboard XiangMask[90];                   // 相,主要是用来算一下象眼,
extern int      XiangAttackIndex[90];
#define NUM_XIANG_ATT    (300)
extern Bitboard XiangAttacks[NUM_XIANG_ATT];

extern Bitboard SetMaskBB[90];
extern Bitboard ClearMaskBB[90];
extern Bitboard Che_Mask_FR[90];                // 车用来计算棋步的少最后一位,不包括自己
extern Bitboard Che_Mask_F[90];                 // 车FILE MASK, 不包括自己
extern Bitboard Che_Mask_R[90];                 // 车RANK MASK, 不包括自己
extern Bitboard ChePseudoMask_FR[90];           // 车可攻击的位,包括最后一位
extern Bitboard MaKingAttackZone[90];           // 棋子可攻击将的能力.
extern Bitboard MaPosAttackKing[90];            // 马攻击将的棋格
extern Bitboard PawnKingAttackZone[90];         // 棋子可攻击将的能力.
//extern Bitboard Ma_good_mask[2];                // 双方马不太好走的步子


#define NUM_CHE_ATT_R    (11520)
extern Bitboard CheAttacks_R[NUM_CHE_ATT_R];
extern int      CheAttackIndex_R[90];

#define NUM_CHE_ATT_F    (23040)
extern Bitboard CheAttacks_F[NUM_CHE_ATT_F];
extern int      CheAttackIndex_F[90];

#define NUM_PAO_EAT_ATT_R (11520)
extern Bitboard Pao_Eat_Attacks_R[NUM_PAO_EAT_ATT_R];
extern int      Pao_Eat_AttackIndex_R[90];

#define NUM_PAO_EAT_ATT_F (23040)
extern Bitboard Pao_Eat_Attacks_F[NUM_PAO_EAT_ATT_F];
extern int      Pao_Eat_AttackIndex_F[90];

#define NUM_PAO_SUPER_ATT_R (11520)
extern Bitboard PaoSUPER_R[NUM_PAO_SUPER_ATT_R];
extern int      PaoSUPERIndex_R[90];

#define NUM_PAO_SUPER_ATT_F (23040)
extern Bitboard PaoSUPER_F[NUM_PAO_SUPER_ATT_F];
extern int      PaoSUPERIndex_F[90];

extern Bitboard FileBB_A[9];
extern Bitboard RankBB_A[10];
extern Bitboard LowBB[10];          // 棋子下面的位棋盘
extern Bitboard UpBB[10];           // 棋子上面的位棋盘
extern Bitboard LeftBB[9];          // 棋子左边的位棋盘
extern Bitboard RightBB[9];         // 棋子右边的位棋盘
extern Bitboard BetweenBB[90][90];  // 二个在同一线上的棋子之间的位棋盘．不包括自己的信息.


#define m128_from_2u64(bb,data0,data1)  (bb = _mm_set_epi64x(data0,data1))

#define m_not(bb) _mm_andnot_si128(bb,ALL_B90)

#define m_xor(xmm1,xmm2) _mm_xor_si128(xmm1, xmm2)

#define m_and(xmm1,xmm2) _mm_and_si128(xmm1, xmm2)

#define m_or(xmm1,xmm2)  _mm_or_si128 (xmm1, xmm2)


#define BB_u64(bb,i) (bb).m128i_u64[i]
#define BB_i64(bb,i) (bb).m128i_i64[i]

#define set_mask_bb(s)    SetMaskBB[s]
#define clear_mask_bb(s)  ClearMaskBB[s]


#define M128_get_Or64(bb)        (_mm_extract_epi64(bb,1) | _mm_extract_epi64(bb,0))
//////////////////////////////////////////////////////////////////////////
#define transform_bbm(bb,magic64,bits)  ((M128_get_Or64(bb) * (magic64)) >> (bits))
#define transform_mul(bb,magic64,bits)  ((M128_get_Or64(bb) * (magic64)) >> (64 - (bits)))

#define transform_bba(bb,magic64,bits)  ((M128_get_Or64(bb) * (magic64)) >> (bits));
#define get_transfrom_u64(bb,magic64)  (M128_get_Or64(bb) * (magic64))


__inline int count_1s(Bitboard bb) {
	return (_mm_popcnt_u64(_mm_extract_epi64(bb, 0)) + _mm_popcnt_u64(_mm_extract_epi64(bb, 1)));
}

__inline int count_1s(Bitboard b1, Bitboard b2) {
	Bitboard bb = m_and(b1, b2);
	return (_mm_popcnt_u64(_mm_extract_epi64(bb, 0)) + _mm_popcnt_u64(_mm_extract_epi64(bb, 1)));
}

__inline bool m128_is_same(Bitboard& b1, Bitboard& b2) {
	Bitboard x = _mm_xor_si128(b1, b2);
	return _mm_testz_si128(x, x);
}


__inline bool m_have_bit(Bitboard m128) {  // 这个快，晕
	return !_mm_testz_si128(m128, m128);
}


#define have_bit(b1,b2)     (!_mm_testz_si128(b1,b2))
#define bit_is_set(bb,sq)   (_mm_testc_si128(bb,SetMaskBB[sq]))

#define set_bit(bb,sq)     (bb = _mm_or_si128(bb,SetMaskBB[sq]))
#define clear_bit(bb,sq)   (bb = _mm_and_si128(bb,ClearMaskBB[sq]))


#define m_Lsf(bb,count) {\
	Bitboard sltmp; \
	sltmp = _mm_slli_si128(bb,8);\
	sltmp = _mm_srli_epi64(sltmp,64-(count));\
	bb   = _mm_slli_epi64(bb,count);\
	bb   = _mm_or_si128(bb,sltmp);\
}

#define m_Rsf(bb,count) {\
	Bitboard sltmp; \
	sltmp = _mm_srli_si128(bb,8);\
	sltmp = _mm_slli_epi64(sltmp,64-(count));\
	bb   = _mm_srli_epi64(bb,count);\
	bb   = _mm_or_si128(bb,sltmp);\
}

__inline Square lsb(quint64 b) {
	unsigned long index;
	_BitScanForward64(&index, b);
	return (Square)index;
}

__inline Square pop_lsb(quint64* b) {
	const Square s = lsb(*b);
	*b &= *b - 1;
	return s;
}

__inline Square pop_1st_bit_old(Bitboard& b) {	//_BitScanForward
	unsigned long index;
	if (_mm_extract_epi64(b, 0)) {
		_BitScanForward64(&index, _mm_extract_epi64(b, 0));
	}
	else {
		_BitScanForward64(&index, _mm_extract_epi64(b, 1));
		index += 64;
	}
	clear_bit(b, index);
	return (Square)index;
}




__inline Square pop_1st_bit_sq(Bitboard& b) {
	unsigned long index;
	if (_mm_extract_epi64(b, 0)) {
		__int64 a0 = _mm_extract_epi64(b, 0);
		_BitScanForward64(&index, a0);

		a0 &= a0 - 1;
		b = _mm_insert_epi64(b, a0, 0);
	}
	else {
		__int64 a1 = _mm_extract_epi64(b, 1);
		_BitScanForward64(&index, a1);

		a1 &= a1 - 1;
		b = _mm_insert_epi64(b, a1, 1);

		index += 64;
	}
	return (Square)index;
}


__inline bool pop_1st_bit_sq(Bitboard& b, Square& sq) {

	if (_mm_testz_si128(b, b)) {
		return false;
	}

	unsigned long index;
	if (_mm_extract_epi64(b, 0)) {
		__int64 a0 = _mm_extract_epi64(b, 0);
		_BitScanForward64(&index, a0);

		a0 &= a0 - 1;
		b = _mm_insert_epi64(b, a0, 0);

		sq = (Square)index;
	}
	else if (_mm_extract_epi64(b, 1)) {
		__int64 a1 = _mm_extract_epi64(b, 1);
		_BitScanForward64(&index, a1);

		a1 &= a1 - 1;
		b = _mm_insert_epi64(b, a1, 1);

		index += 64;
		sq = (Square)index;
	}

	return true;
}



enum BoardStatus
{
    Valid, NoWhiteKing, NoBlackKing, DoubleCheck,
    OppositeCheck, TooManyBlackPawns, TooManyWhitePawns,
    PawnsOn18, TooManyKings, TooManyWhite, TooManyBlack,
    BadCastlingRights, InvalidEnPassant, MultiCheck
};

//typedef uchar CastlingRights;
//enum
//{
//    NoRights = 0,
//    WhiteKingside = 1, BlackKingside = 2,
//    WhiteQueenside = 4, BlackQueenside = 8,
//    WhiteBothSides = 5, BlackBothSides = 10,
//    AllRights = 15
//};

/** @ingroup Core
 * Keep track of the pieces on a chessboard, provide a Move() factory.
 */
class CBoard
{
public:
    CBoard();

    // Play moves on board
    //
    /** Play given move, updating board state appropriately */
    bool doMove(const Move&);
    /** Return board to state prior to given move */
    void undoMove(const Move&);

    // Setup board
    //
    /** Remove all pieces and state from board */
    void clear();
    /** Set move number in game */
    void setMoveNumber(unsigned int moveNumber);
    /** Set initial chess game position on the board */
    void setStandardPosition();
    /** Set the given piece on the board at the given square */
    void setAt(const Square s, const Piece p);
    /** Remove any piece sitting on given square */
    void removeAt(const Square s);
    /** Set side to move as that of given color */
    void setToMove(const Color& c);
    /** Swap the side to move */
    void swapToMove();
    /** Parse given FEN, return true if loaded properly otherwise false */
    bool fromFen(const QString& fen);
    /** Set En Passant Square */
    //void setEnPassantSquare(const Square s);
    /** Set En Passant in a file */
    //void setEnPassantFile(int f);
    /** From a FICS representation of a board */
    bool from64Char(const QString &qcharboard);
    /** Remove En Passant privilege */
    //void clearEnPassantSquare();

    // Move factories
    //
    /** parse SAN or LAN representation of move, and return proper Move() object */
    Move parseMove(const QString& algebraic) const;
    /** Return a proper Move() object given only a from-to move specification */
    Move prepareMove(const Square& from, const Square& to) const;

    // Return a nullMove -- King to the same square
    Move nullMove() const;

    // Query
    //
    /** Is piece sitting on given square moveable ? */
    bool isMovable(const Square s) const;
    /** @return piece sitting at given square on the board */
    Piece pieceAt(Square s) const;
    /* Get the color of a Piece at square @s */
    Color colorAt(Square s) const;
    /** @return number of ply since a pawn move or capture */
    unsigned int halfMoveClock() const;
    /** Set number of ply since a pawn move or capture */
    void setHalfMoveClock(unsigned int i);
    /** @return the current move number in the game */
    unsigned int moveNumber() const;
    /** @return color of side next to move */
    Color toMove() const;
    /** @return true if color of side next to move is black */
    bool blackToMove() const;
    /** @return true if color of side next to move is black */
    bool whiteToMove() const;
    /** @return true if its possible for this position to follow target position */
    bool canBeReachedFrom(const CBoard& target) const;
    /** @return true if position is same, but don't consider Move # in determination */
    bool positionIsSame(const CBoard& target) const;
    /** @return true if neither side can win the game */
    bool insufficientMaterial() const;
    /** @return the square at which the king of @p color is located */
    Square kingSquare(Color color) const;

    // Query other formats
    //
    /** Return a FEN string based on current board position */
    QString toFen(bool forceExtendedFEN=false) const;
    /** Return a FEN string in human readable format based on current board position */
    QString toHumanFen() const;
    /** Return a SAN string representation of given move */
    QString moveToSan(const Move& move, bool translate = false, bool extend = false) const;
    /** @return a SAN string representing a given move with move number. */
    QString moveToFullSan(const Move& move, bool translate=false) const;

    // Validation
    //
    /** Check current position and return "Valid" or problem */
    BoardStatus validate() const;
    /** Return true if given FEN can be parsed */
    bool isValidFen(const QString& fen) const;

    /** Set castling rights. */
    //void setCastlingRights(CastlingRights cr);
    /** Return the internal castling rights data (used by hash function) */
    //CastlingRights castlingRights() const;
    /** Return square where En passant capture may occur, or "NoEPSquare" */
    //Square enPassantSquare() const;

    //bool canTakeEnPassant() const;
    /** Return true if the side to move is in checkmate */
    bool isCheckmate() const;
    /** Return true if the side to move is stalemated */
    //bool isStalemate() const;

    /** Return 1 if Chess960 is selected, 0 otherwise */
    //bool chess960() const;
    /** Set to 1 if Chess960 is selected, 0 otherwise */
    //void setChess960(bool chess960);
    /** Setup board according to position number */
    void fromChess960pos(int value);
    /** Get the position number from the current position */
    int chess960Pos() const;
    //quint64 castlingRooks() const;
    //static quint64 standardCastlingRooks();

    //void setCastlingRooks(char file000=0, char file00=0);
    //int CastlingRookIndex(Square rook) const;
    //bool HasRookOnFileForCastling(unsigned char file, bool castle000) const;

    //bool hasAmbiguousCastlingRooks(char file000 = 0, char file00 = 0) const;
    /** Test to see if given color has the right to castle on kingside */
    //bool canCastleShort(const unsigned int color) const;
    /** Test to see if given color has the right to castle on queenside */
    //bool canCastleLong(const unsigned int color) const;
    /** Get the castling rook to the given index into m_castlingRook */
    //Square CastlingRook(int index) const;
    /** Return the square of the king if in check, InvalidSquare otherwise */
    Square kingInCheck() const;
    /** Return true if the given square is attacked by the given color */
    bool isAttackedBy(const unsigned int color, Square square) const;
    /** Return number of attacks onto a given square by the given color */
    int numAttackedBy(const unsigned int color, Square square) const;
    /** Generate all possible moves in a given position */
    MoveList generateMoves() const;
protected:
    unsigned int countSetBits(quint64 n) const;
private:
    /** Test if a king is on a certain row to test castling rights */
    bool isKingOnRow(Piece p, Square start, Square stop) const;
    /** Return true if side to move is in check */
    bool isCheck() const;

    /** Test to see if given color has any castling rights remaining */
    //bool canCastle(const unsigned int color) const;

    /** Return true if making move would put oneself into check */
    bool isIntoCheck(const Move& move) const;
    /** Return true if the given squares are attacked by the given color */
    bool isAttackedBy(const unsigned int color, Square start, Square stop) const;

    /** Return all squares attacked by a knight on given square */
    quint64 knightAttacksFrom(const Square s) const;
    /** Return all squares attacked by a bishop on given square */
    quint64 bishopAttacksFrom(const Square s) const;
    /** Return all squares attacked by a rook on given square */
    quint64 rookAttacksFrom(const Square s) const;
    /** Return all squares attacked by a queen on given square */
    quint64 queenAttacksFrom(const Square s) const;
    /** Return all squares attacked by a king on given square */
    quint64 kingAttacksFrom(const Square s) const;
    /** Return all possible pawn moves from given square */
    quint64 pawnMovesFrom(const Square s) const;

    /** Remove impossible moves from given bitboard to aid disambiguation */
    void removeIllegal(const Move& move, quint64& b) const;
    /** Update move with castling details, return false if no castle is possible */
    //bool prepareCastle(Move& move) const;
    /** Update move with castling details for Chess960, return false if no castle is possible */
    //bool prepareCastle960(Move &move) const;
    /** Test that nothing is inbetween the castling pieces */
    //bool isFreeForCastling960(Square from, Square to, Square rook_from, Square rook_to) const;


    /** Grant castling rights on the kingside to the given color */
    //void setCastleShort(unsigned int color);
    /** Grant castling rights on the queenside to the given color */
    //void setCastleLong(unsigned int color);
    /** Revoke all castling rights from the given color */
    //void destroyCastle(unsigned int color);
    /** Revoke castling rights from the given color */
    //void destroyCastleInDirection(unsigned int color, Square s);
    /** Update the epSquare value based on a new epFile value */
    //void epFile2Square();

    /** Setup board according to FEN string */
    bool fromGoodFen(const QString& fen);
    /** Get the rook with index from castling rook storage */
    //bool HasRookForCastling(int index) const;
    //Square CastlingKingTarget(int rookIndex) const;
    //Square CastlingRookTarget(int rookIndex) const;
    //void fixCastlingRooks(bool, char file000=0, char file00=0);

    // Actual Bit-board data
	//quint64 m_pawns, m_knights, m_bishops, m_rooks;
	//quint64 m_castlingRooks;
	//quint64 m_queens, m_kings;

	Bitboard m_ches;
	Bitboard m_mas;
	Bitboard m_paos;
	Bitboard m_shis;
	Bitboard m_xiangs;
	Bitboard m_kings;
	Bitboard m_pawns;

	Bitboard m_occupied_co[2];     // Square mask of those occupied by each color
	Bitboard m_occupied;           // Square is empty or holds a piece
    //quint64 m_occupied_l90;       // rotated counter clockwise 90 deg
    //quint64 m_occupied_l45;       // an odd transformation, to straighten out diagonals
    //quint64 m_occupied_r45;       // the opposite odd transformation, just as messy

    // Extra state data
    unsigned char m_piece[90];             // type of piece on this square
    unsigned char m_stm;                   // side to move
    Square        m_ksq[2];                // square of the m_kings
    //unsigned char m_epFile;                // file of a possible ep capture
    //unsigned char m_epSquare;              // This is requested by hash routine enough that we keep it pre calculated
    //unsigned char m_castle;                // flags for castle legality  (these can be merged)
    unsigned short m_halfMoves;            // Number of moves since last pawn move or capture
    unsigned int m_moveNumber;             // Move number in game (incremented after each black move)
    //unsigned char m_pawnCount[2];          // Number of pawns for each side
    unsigned char m_pieceCount[2];         // Number of pieces INCLUDING pawns for each side
    //unsigned char m_chess960;              // 0 = standard, 1 = Chess960
};

//enum Char64Position
//{
//    C64_ROW8,
//    C64_ROW7,
//    C64_ROW6,
//    C64_ROW5,
//    C64_ROW4,
//    C64_ROW3,
//    C64_ROW2,
//    C64_ROW1,
//    C64_COLOR_TO_MOVE,
//    C64_COL_DOUBLE_PAWN_PUSH,
//    C64_CASTLE_W_00,
//    C64_CASTLE_W_000,
//    C64_CASTLE_B_00,
//    C64_CASTLE_B_000,
//    C64_PLY_50_MOVE,
//    C64_NUM_GAME,
//    C64_NAME_WHITE,
//    C64_NAME_BLACK,
//    C64_GAME_RELATION,
//    C64_INITIAL_TIME_S,
//    C64_INCREMENT_S,
//    C64_MATERIAL_WHITE,
//    C64_MATERIAL_BLACK,
//    C64_REMAINDER_TIME_WHITE,
//    C64_REMAINDER_TIME_BLACK,
//    C64_NEXT_MOVE_NUMBER,
//    C64_LAST_MOVE,
//    C64_ELAPSED_TIME_LAST_MOVE,
//    C64_PP_LAST_MOVE,
//    C64_FLIP_BOARD,
//    C64_CLOCK_RUNNING,
//    C64_LAG
//};
//
//enum Char64Relation
//{
//    C64_REL_ISOLATED = -3,           // isolated position, such as for "ref 3" or the "sposition" command
//    C64_REL_OBSERVING_EXAMINE = -2,  // I am observing game being examined
//    C64_REL_PLAY_OPPONENT_MOVE = -1, // I am playing, it is my opponent's move
//    C64_REL_OBSERVING_PLAY = 0,      // I am observing a game being played
//    C64_REL_PLAY_MY_MOVE = 1,        // I am playing and it is my move
//    C64_REL_EXAMINE = 2              // I am the examiner of this game
//};

//extern quint64 bb_PawnAttacks[2][64];
//extern quint64 bb_KnightAttacks[64];
//extern quint64 bb_R45Attacks[64][64];
//extern quint64 bb_L45Attacks[64][64];
//extern quint64 bb_KingAttacks[64];
//extern quint64 bb_RankAttacks[64][64];
//extern quint64 bb_FileAttacks[64][64];

//const unsigned int bb_ShiftR45[64] =
//{
//    1, 58, 51, 44, 37, 30, 23, 16,
//    9, 1, 58, 51, 44, 37, 30, 23,
//    17, 9, 1, 58, 51, 44, 37, 30,
//    25, 17, 9, 1, 58, 51, 44, 37,
//    33, 25, 17, 9, 1, 58, 51, 44,
//    41, 33, 25, 17, 9, 1, 58, 51,
//    49, 41, 33, 25, 17, 9, 1, 58,
//    57, 49, 41, 33, 25, 17, 9, 1
//};
//
//const unsigned int bb_ShiftL45[64] =
//{
//    9, 17, 25, 33, 41, 49, 57, 1,
//    17, 25, 33, 41, 49, 57, 1, 10,
//    25, 33, 41, 49, 57, 1, 10, 19,
//    33, 41, 49, 57, 1, 10, 19, 28,
//    41, 49, 57, 1, 10, 19, 28, 37,
//    49, 57, 1, 10, 19, 28, 37, 46,
//    57, 1, 10, 19, 28, 37, 46, 55,
//    1, 10, 19, 28, 37, 46, 55, 64
//};

inline bool CBoard::isAttackedBy(const unsigned int color, Square square) const
{
    //if(bb_PawnAttacks[color ^ 1][square] & m_pawns & m_occupied_co[color])
    //{
    //    return 1;
    //}
    //if(knightAttacksFrom(square) & m_knights & m_occupied_co[color])
    //{
    //    return 1;
    //}
    //if(bishopAttacksFrom(square) & (m_bishops | m_queens) & m_occupied_co[color])
    //{
    //    return 1;
    //}
    //if(rookAttacksFrom(square) & (m_rooks | m_queens) & m_occupied_co[color])
    //{
    //    return 1;
    //}
    //if(kingAttacksFrom(square) & m_kings & m_occupied_co[color])
    //{
    //    return 1;
    //}
    return 0;
};

inline bool CBoard::isAttackedBy(const unsigned int color, Square start, Square stop) const
{
    Square square = start;

    while(square!=stop)
    {
        bool underAttack = isAttackedBy(color, square);
        if (underAttack) return true;
        if (square!=stop) square += (start<=stop) ? 1:-1;
    }

    return isAttackedBy(color, stop);
};

//inline void CBoard::setCastleShort(unsigned int color)
//{
//    m_castle |= 1 << color;
//}

//inline void CBoard::setCastleLong(unsigned int color)
//{
//    m_castle |= 4 << color;
//}

//inline void CBoard::destroyCastle(unsigned int color)
//{
//    m_castle &= ~(5 << color);
//}

//inline void CBoard::destroyCastleInDirection(unsigned int color, Square s)
//{
//    for (int i = 0; i<4; ++i)
//    {
//        if (CastlingRook(i) == s)
//        {
//            switch(i)
//            {
//            case 0: if (color == 0) m_castle &= (unsigned char) ~4; break;
//            case 1: if (color == 0) m_castle &= (unsigned char) ~1; break;
//            case 2: if (color == 1) m_castle &= (unsigned char) ~8; break;
//            case 3: if (color == 1) m_castle &= (unsigned char) ~2; break;
//            }
//            break;
//        }
//    }
//}

inline quint64 CBoard::knightAttacksFrom(const Square s) const
{
    //return bb_KnightAttacks[s];
	return quint64();
}

inline quint64 CBoard::bishopAttacksFrom(const Square s) const
{
    //return bb_R45Attacks[s][(m_occupied_r45 >> bb_ShiftR45[s]) & 63] |
    //       bb_L45Attacks[s][(m_occupied_l45 >> bb_ShiftL45[s]) & 63];
	return quint64();
}

inline quint64 CBoard::rookAttacksFrom(const Square s) const
{
    //return bb_RankAttacks[s][(m_occupied >> ((s & ~7) + 1)) & 63] |
    //       bb_FileAttacks[s][(m_occupied_l90 >> (((s & 7) << 3) + 1)) & 63];
	return quint64();
}

inline quint64 CBoard::queenAttacksFrom(const Square s) const
{
    return rookAttacksFrom(s) | bishopAttacksFrom(s);
}

inline quint64 CBoard::kingAttacksFrom(const Square s)  const
{
    //return bb_KingAttacks[s];
	return quint64();
}

//inline void CBoard::epFile2Square()
//{
//    if(m_epFile)
//    {
//        m_epSquare = m_epFile + (m_stm == White ? a6 : a3) - 1;
//    }
//    else
//    {
//        m_epSquare = NoEPSquare;
//    }
//}

//inline bool CBoard::canCastle(const unsigned int color) const
//{
//    return m_castle & (5 << color);
//}

//inline bool CBoard::canCastleShort(const unsigned int color) const
//{
//    return m_castle & (1 << color);
//}

//inline bool CBoard::canCastleLong(const unsigned int color)  const
//{
//    return m_castle & (4 << color);
//}

inline bool CBoard::isCheck() const
{
    return isAttackedBy(m_stm ^ 1, m_ksq[m_stm]);
}

inline Square CBoard::kingInCheck() const
{
    return isCheck() ? m_ksq[m_stm] : (Square) InvalidSquare;
}

inline unsigned int CBoard::halfMoveClock() const
{
    return m_halfMoves;
}

inline void CBoard::setHalfMoveClock(unsigned int i)
{
    m_halfMoves = i;
}

inline unsigned int CBoard::moveNumber() const
{
    return m_moveNumber;
}

inline Color CBoard::toMove() const
{
    return Color(m_stm);
}

inline bool CBoard::blackToMove() const
{
    return Color(m_stm) == Black;
}

inline bool CBoard::whiteToMove() const
{
    return Color(m_stm) == White;
}

//inline Square CBoard::enPassantSquare() const
//{
//    return Square(m_epSquare);
//}
//
//inline CastlingRights CBoard::castlingRights() const
//{
//    return m_castle;
//}

extern  void init_bb_const(void);
extern void init_bitboards();

#endif // BITBOARD_H_INCLUDED
