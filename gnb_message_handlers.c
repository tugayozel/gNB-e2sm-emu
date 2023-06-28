//
// Created by Eugenio Moro on 04/24/23.
//

#include "gnb_message_handlers.h"
#include <stdbool.h>
#define CONNECTED_UES 4

int gnb_id = 0;
bool is_initialized = false;
typedef struct {
    int rnti;
    char* prop_1;
    float prop_2;
} ue_struct;
ue_struct connected_ue_list[CONNECTED_UES];

float randomBER16()
{
    float dataset_16[457] = {0.02680072043642437,0.0304260199805865,0.03436048645391923,0.028400655486224752,0.03952877179955752,0.00920620655217333,0.03473716049377709,0.0219440338989402,0.03627514594582673,0.016270603369982345,0.01809436003167955,0.03452630087604516,0.034281189513083815,0.02982602638028911,0.002555660859504455,0.036469352690275875,0.019571136865136923,0.03777830068978952,0.0412485435577398,0.003204534308070578,0.019372767930779494,0.03266650867873824,0.028194841508748875,0.03283291870284502,0.02720256960930048,0.026235091262741733,0.0327035271406341,0.040397892263611374,0.03350048048800716,0.03168332517801478,0.010601349369860374,0.033324168064575194,0.03450329432844437,0.03582583121703556,0.009441899955781846,0.011000788413427914,0.009375425552692468,0.03345302150942256,0.022336998495032484,0.02794815768284878,0.037344607334820396,0.04102024348666458,0.002694370944944874,0.018669418853826697,0.03948804799767239,0.016059747666952756,0.028759908759342784,0.04173701471022753,0.0388534686729162,0.038623705095831046,0.005441490583522862,0.03820982273362597,0.03828597585743512,0.02589989577056287,0.018697317262386465,0.040967986883292534,0.019144247264210185,0.02275078207461237,0.03599286726648501,0.022186709478196592,0.02961665730151744,0.006118911081933437,0.04176881987933592,0.033298860650850554,0.03908630125339366,0.03376681697127429,0.016684270916982463,0.035995739010176525,0.037350246755658484,0.013238169383945092,0.03232520375685857,0.03655656913715047,0.00790427589327472,0.030248315750301208,0.01911066738750114,0.020756418882009436,0.023808742633883245,0.01158553573822299,0.01822170393149261,0.02671358697249318,0.04031654683627309,0.024457395419220124,0.008399906165011878,0.04031611919349279,0.03786529920033957,0.028501606313044242,0.02766168282746398,0.032579188805425124,0.03083053331694488,0.03362811645843081,0.016949745812698952,0.030981783567361504,0.03132118675986742,0.03974524407414451,0.020130803377471557,0.03301258317570746,0.03455075265300325,0.03267007337919706,0.03465235588017937,0.02795649635950262,0.03912141190980725,0.029005161372223226,0.03354298484863519,0.03327360635247581,0.01777096965913963,0.040070013196452786,0.002123394887512481,0.034856849703348264,0.011163608282635545,0.0325391153458289,0.03853935365588104,0.023884409903831033,0.04117293567307048,0.03390398093975358,0.022116770774878086,0.030847675050526574,0.022307095540525484,0.03692660776428727,0.022247969885005686,0.030413180185083016,0.0359405393745508,0.02541888623530278,0.026939795687901752,0.03960011826060664,0.03716491989211171,0.02867671655210549,0.03905918053100735,0.03681534589642546,0.019290405847002617,0.009873959376135583,0.03687405346357933,0.025587188260372568,0.04160888931422449,0.03499779516587412,0.02411626256201896,0.013069331610114393,0.036193744241043296,0.030552763472183525,0.03823772053578814,0.028163781400319193,0.032399622905972786,0.026016061307683552,0.03294848972076672,0.03446931844685289,0.030471536690924866,0.00333049768567642,0.0211340959777854,0.0064968933964658915,0.02791559219674325,0.02007754228289685,0.0022643034811164198,0.035072630711186076,0.007343136256802968,0.03468713126799031,0.03743080872969742,0.03281344441998138,0.03860560838181906,0.03697481543752926,0.023166850038306347,0.03869290728034894,0.02353549201475183,0.04067968256071866,0.03887211020469153,0.04047254245732726,0.03366123261425527,0.038721113780918165,0.0401688938371311,0.031869725935583265,0.04037318537572179,0.02344914278436719,0.04145597432028661,0.0358441227241805,0.036084142668638824,0.023327941586272744,0.0290661147260928,0.004480174084840055,0.029957231088850872,0.04089280320054525,0.026766513449920787,0.03461809107068983,0.03203675010771537,0.03379065170836118,0.025796678971596126,0.03425767529891047,0.029995458533639413,0.02505159153622874,0.022906834445862195,0.019208127329113506,0.02121575135850487,0.039822227417008055,0.027986096260960075,0.03800618991183349,0.027220190540147154,0.03811063926020988,0.03006527491493008,0.03634811752680625,0.03532901619398646,0.02990768431010929,0.04167204227207236,0.02967544124908819,0.03587298056846114,0.02726958570106333,0.01296283953001201,0.009802362786033886,0.013240602808894858,0.014327180408991641,0.030479034587752724,0.027811608900929624,0.038024510942166106,0.019560845233115215,0.015252674872318212,0.03460182274117721,0.03541669119066962,0.03693246544216114,0.016142671683727322,0.038527216703064054,0.0048522676177335244,0.022421145868052467,0.037658098654993616,0.020213156954939665,0.03717693703417804,0.025372794768603463,0.03358031017831023,0.03273678192759513,0.029381315653902146,0.020897771734786824,0.013028739968832165,0.03703989856776016,0.01845728776390612,0.03142060606619626,0.03251142275592858,0.025067305333985962,0.03343999904649278,0.025432886583878128,0.007981237758358933,0.04150469016036387,0.03862566522821856,0.0392958943933798,0.011857647005288158,0.038550595972676766,0.02734794643021235,0.0265340881581341,0.03287638149145736,0.039955475819246994,0.01360806832772768,0.03962068595598969,0.005620976616883239,0.03868692572989288,0.02814335778937363,0.02851369213372515,0.01705195968515208,0.04079606829322349,0.013803415988681872,0.03785762978814913,0.0412090720296924,0.02363824047184307,0.00379260456407296,0.0066344835665956,0.01570798442194024,0.012967746553146947,0.02125995894111457,0.04057406620408979,0.030178368868728628,0.03287107968078731,0.03801774984852049,0.02672941320174052,0.03454177737628519,0.0288904496729733,0.039259013754056854,0.0339239233221528,0.010964334075542231,0.04074686330285063,0.03995025209624728,0.03731280146924468,0.039953358436746106,0.030853074991035984,0.04086184154766462,0.032439649532952114,0.03576184323613166,0.03385802522953166,0.03819342514915039,0.03287835264051911,0.04002080894737317,0.029595716474933337,0.028667162542810015,0.021666983366937537,0.02899481568084386,0.03436272369206064,0.03931295226263001,0.02234611329648986,0.04063601211863746,0.03310909675437271,0.010948904556245559,0.02657519078817963,0.012390116870633433,0.03258147015597937,0.03182865401818638,0.04158925850738884,0.023476810818535615,0.029885803049385956,0.04113321257225158,0.037651340012139795,0.02856128482040013,0.008997019126170486,0.018397448977087866,0.041681749977090427,0.024862165068537584,0.006080769858564011,0.029776984138941837,0.0386306655033232,0.0023626272176974494,0.011790095610012236,0.031916890396442105,0.033587528233234215,0.028302124745030938,0.001843892101479977,0.04087399536778849,0.022587184411486133,0.04074303324357978,0.033409358062055056,0.02443304759244383,0.029906731211762155,0.0035931167477322445,0.01655323958023383,0.03565154428749931,0.010391124182326822,0.007724236272174251,0.028344047416379775,0.03402741467085005,0.03905188125815587,0.018647593033440796,0.03885156158940731,0.030938956259887324,0.03475574603899126,0.02920195042907739,0.03946252608890402,0.028943826516578147,0.019395474454447698,0.017277971415066956,0.030297884172110573,0.039130912336188844,0.03151412372463716,0.004112594793649699,0.03097225197437306,0.019001640033105144,0.009100600915641938,0.027457949866298487,0.026921394087776745,0.034936819785186174,0.011578528296396634,0.02714576092212098,0.01907512288014504,0.03846645598762902,0.029495426863775626,0.03803421835941548,0.015569758207719137,0.03919316050707336,0.03785639424889245,0.027420726137204282,0.02806115048375593,0.03905695422467251,0.006947195537396228,0.03354403674298259,0.004759661314874292,0.03787220158416474,0.036713580093883286,0.016746711605586745,0.029102758539485768,0.03374903080004579,0.020386834211557986,0.02545885041082188,0.025247507227783045,0.01157142169473549,0.03919611271419479,0.01685160192867388,0.033486488395842035,0.03055512281122033,0.002128963985572746,0.02373119937626869,0.007670930688286198,0.03985518218800946,0.022454436500945057,0.03676545401295042,0.016713149002332367,0.026955762819041246,0.03426969332367738,0.025888324472245344,0.02221930396151231,0.03415094029710111,0.03999952149047195,0.030555886412120176,0.034310955784443126,0.03563199842951584,0.013134120047297332,0.035383656848392425,0.041653347542703806,0.041035241056456645,0.0390650780712615,0.02850176440724775,0.01625095480920416,0.03411538960664165,0.03643706525331494,0.03665644361412937,0.03602726633113687,0.03495488831457308,0.01811074668236548,0.03510625048626817,0.019252705035169543,0.029864421237689426,0.04137694030976405,0.027894378721936924,0.023481023652777294,0.013913111410768814,0.04066496158085356,0.03893194453142837,0.03432034833034617,0.04022126523390726,0.034194766688900785,0.0195580597038644,0.025080149942866697,0.039408580094370566,0.03716246001815607,0.02981344855206927,0.009795108734187569,0.01940953866843889,0.04173110989133191,0.006553180128614194,0.00951438750210079,0.032658617354399594,0.03387781652935687,0.035583078187900435,0.02315290891672231,0.029257842119285865,0.036972167009629825,0.015433861403972321,0.03774218600231119,0.011413311984635716,0.037455770038982955,0.03580852672220827,0.025905860247169038,0.04177480725810892,0.009257907721143571,0.0206334770586262,0.024396877136075995,0.016321141684510293,0.033165864381485305,0.03209004864835943,0.03428402114090848,0.037630857948031476,0.037554372779250805,0.025025056175825094,0.0405633342271107,0.03739804329270405,0.0381010597861661,0.03186166836888407,0.03179460953190519,0.03556123639550193};

    // Randomly select a number from the dataset
    float selectedBER = dataset_16[rand() % 457];

    return selectedBER;
}

float randomBER64()
{
    float dataset_64[530] = {0.03927323146785722,0.0305725845055258,0.02954176444553891,0.028774491799029356,0.0664414332945027,0.030060004007474328,0.0882554932444739,0.040352862427856406,0.059415663514613914,0.056185741027479974,0.07270996638768445,0.07663609916236358,0.04301726174393661,0.04236986725834879,0.050214247226509245,0.02730065507854773,0.0350537577808554,0.04714006386569536,0.03121140615213136,0.03411668097419973,0.09748278114829856,0.04020517683791569,0.03648053191021394,0.041399646320311234,0.031144895160172936,0.04114026404099502,0.03669820601051765,0.05899966854256267,0.04233336670963994,0.05880847257996269,0.027907756059555977,0.028188025847506237,0.09806659221949632,0.04033570787304819,0.03023508807923303,0.0537667046450756,0.03367310423863179,0.04931787682385669,0.026902188850073783,0.0351706723167835,0.02673818139778472,0.049274294797709395,0.03055183765431968,0.06731243238403284,0.068824746408777,0.04112548538630634,0.0713750126571342,0.037057762449741016,0.02929347541533578,0.08056593346222485,0.05443033857080848,0.03183454525880003,0.02681676863414073,0.0839472817828455,0.08063027478120399,0.033210692904447336,0.028426560230332187,0.07207788311786567,0.03137868870387517,0.06510872899226183,0.04411512424353159,0.03917454239153084,0.03719705886519131,0.05834703748071002,0.03893104376241241,0.029200749925912373,0.02989303555376277,0.029570332634513585,0.03103282493221382,0.03410317637109328,0.04381930063710837,0.03004681591417535,0.040796253801395066,0.04438087062617324,0.0353563688125329,0.04373828437795435,0.0400585034697607,0.029830961601369,0.06897174418487118,0.0657611940206404,0.0444215852216403,0.05589494527238892,0.03749249522540721,0.02757921957838816,0.09844356393194986,0.04497529636265285,0.02888571339523538,0.044439582756470974,0.05905321584158352,0.027969257477366005,0.03189738746679338,0.030531877781543537,0.032037273378061615,0.04719575204668769,0.035445919093932465,0.02695644532708985,0.06347709256503298,0.0488400285970878,0.04922623956156147,0.03164941229000817,0.027213168439749635,0.029145800646905196,0.04386160348256474,0.04190217174226585,0.051442504813606904,0.049810482820946245,0.04614739699000436,0.05621939913220708,0.03496105277714534,0.06745060361340016,0.04885075410720541,0.04313126441237336,0.028875207078363996,0.04616642040462682,0.06340736260083357,0.0360426948706285,0.04689111215372099,0.08640896467722436,0.051689007894376804,0.054781173224521806,0.07645767057394859,0.028365372724939997,0.033428145486452676,0.037171803769444844,0.049971189343788414,0.043248633883324006,0.028898102819288063,0.05116414809287906,0.03281614898726448,0.02788278533608768,0.058053276090332506,0.03845499974808275,0.028345338432290923,0.03932957817291971,0.027763813951648064,0.030443009430968226,0.035398562720421856,0.0495894903317855,0.03172083427149941,0.07819961840238432,0.027160170110557935,0.044600414760699314,0.06321997511016564,0.03839300229898357,0.06915556086210484,0.06726173766920174,0.03847241271383095,0.04063410138244894,0.02761723441304964,0.032659412901258955,0.04684906540686784,0.03897919749522072,0.034491905066236006,0.027876871887874577,0.0936845303463083,0.029554218195184667,0.0398137578851534,0.07231112699081788,0.05495781794487842,0.033026257146695714,0.029437753824765656,0.03480245073592991,0.027223707872894964,0.026700614687109603,0.02773462794364856,0.037366204023756566,0.08321444767883834,0.03334185723208738,0.03866922911465731,0.03862156020595808,0.03354062007556724,0.03608068180781632,0.02780632312438125,0.03879857756316074,0.03718697885854927,0.027147732805679503,0.07054228966564224,0.03624907381703091,0.042107640712323535,0.036866354299763815,0.030272056332766306,0.037250610670160667,0.05799535624744445,0.04206024636074912,0.055398044158229576,0.03960306292920901,0.08033926145630277,0.06549228738382551,0.04819118855003546,0.056401429061222697,0.030711387433904447,0.04357073572141967,0.03789702485395008,0.03193420396146718,0.06062013474527039,0.09939625045530098,0.0885122469946531,0.04666486948711479,0.037438296224086676,0.04445829698330295,0.03351035203097008,0.05231537337263337,0.027110889259228,0.04644947169206226,0.03392758498060244,0.05102312031341594,0.033743181180088344,0.03220201040350035,0.027073119569123616,0.04591460178367579,0.0322539946264877,0.03525279741629128,0.03294617317308268,0.04390911496819694,0.052782147472476115,0.027738514311373974,0.051884808851847986,0.02933303380746355,0.07907360039773459,0.035887881465809235,0.03829688594022751,0.035667260698197145,0.043984058208034194,0.05684187493092718,0.03211218346365774,0.027017870289202994,0.027161629663666087,0.027061611245683626,0.029695560773849605,0.04473047098893601,0.028706434590441532,0.02691813443076785,0.03986885826371189,0.02800156176090507,0.03818994225490435,0.044132587599598594,0.07838213175030129,0.04945306950861017,0.054153472327733265,0.04631516439938532,0.0384071147228211,0.04762756639175336,0.04180938425678837,0.030928121612545434,0.036229850737828695,0.04265451143929844,0.036091307691632046,0.05604729067980285,0.09016651711542001,0.0721131158993884,0.053967890832544274,0.07174045852076105,0.05215571446791856,0.030121723348531804,0.0367406303574751,0.02683434160212861,0.03631328655234034,0.05042696502405053,0.05422321898312288,0.06955256465146076,0.0882390136812814,0.037376726332424726,0.02691892822765496,0.09442024396904714,0.051153794995225654,0.03068803807214504,0.040525359015671114,0.056006991208000345,0.03165845698987679,0.030351313224062926,0.03161809300948182,0.03506472374118719,0.03838862775643026,0.027465379074194995,0.03474854522101878,0.0436138592275408,0.05704524432153324,0.028313608814852564,0.030347714410124516,0.04058029604300373,0.0594989230491052,0.07898468026994832,0.044006676894254415,0.038013739580529116,0.0383209243036402,0.07492333637259119,0.043439873013278785,0.07945805939210793,0.03631616643866664,0.06940254718158934,0.07459555697500231,0.0409946370870482,0.026565848894848587,0.027031847576178825,0.09638496990123757,0.060928169771152785,0.030690843057481265,0.04854761053361423,0.04217951215342608,0.03886855818002233,0.04659067271006534,0.026972635410898338,0.03871161406845958,0.03395742020163972,0.05064273479720782,0.046729582940440606,0.03539076479768477,0.02955234718818267,0.04367473276286127,0.04425209034607369,0.04593972014326053,0.044165788642186454,0.028618172826121224,0.08224987252651061,0.033938188397538926,0.04573525485577723,0.04915236288596336,0.027559395236146145,0.02802444129959758,0.02704253119087041,0.0843351656354876,0.0284945809766759,0.07068386753272415,0.03254247509589159,0.05158506964400256,0.031535318726877204,0.04964634475911023,0.028119813650638203,0.03067749222444638,0.06195899525490112,0.026665761271501998,0.04645855768806029,0.03195729886356724,0.03361257251530558,0.03344138598360136,0.05137605744259921,0.03143655242535126,0.036767294532487726,0.036741247463436766,0.03279998572902909,0.0316570358714261,0.053354813759334485,0.04663291400086478,0.034665364510529484,0.035770859362941554,0.03761929675954989,0.060290947623158564,0.07760904516076228,0.027559635361441348,0.048226007073095545,0.04801128672725419,0.03677604370017162,0.07439552685538242,0.06077082828351954,0.08418172746020613,0.03183291359625828,0.02738660318573327,0.06166276270630222,0.04122370909726958,0.07111162006218197,0.069815103328704,0.04219805441891267,0.037531691772337616,0.042953116934279834,0.03873463415852041,0.029704895503755102,0.031895623934241835,0.02984609786673964,0.040546312729438094,0.03249325128277447,0.03435402286093514,0.03241960311168013,0.027539352971419184,0.035952535327691715,0.029105039843526637,0.03210333449029923,0.04513792869204658,0.06850290385804603,0.03733864051523317,0.043384972683401246,0.08430699391850083,0.04331802675738783,0.028596637325370766,0.028866545022451007,0.027235728860574238,0.06000876587110904,0.04613894869712576,0.03787971555258385,0.047736617353175914,0.042975547936536795,0.03634615167798172,0.02829774014548847,0.03900994535616542,0.03606858522941514,0.04576696027866989,0.048223023425127964,0.05144882044507426,0.07110719216714201,0.039127843041478094,0.03101888719298307,0.0424865971024726,0.038154667000106945,0.03899377318975161,0.06673549226983799,0.05117308132115639,0.06340379823209519,0.03634669098682752,0.04366522933595518,0.05262218303157984,0.046252902560089515,0.026728790570057503,0.029505087244915185,0.028910360502035548,0.03683981011093329,0.06263899399090378,0.06015796166158882,0.049078448511259865,0.03284167311912345,0.031363582068933304,0.05958602882719122,0.028276148726168238,0.02702373940366032,0.061281908802064855,0.043478169541511846,0.027371354996934993,0.051248657822767774,0.039770105937267486,0.0369359278041439,0.026865631789405375,0.028093557833592353,0.03671334512309854,0.03317877566777594,0.03469217649741396,0.029803335080900606,0.033742138185002934,0.029598056174305887,0.027504827041366475,0.09280645581350577,0.057879719071806335,0.04860906783609664,0.0315326160136189,0.04916067236520116,0.05621935629643593,0.02921035851881526,0.04836969763595467,0.0295141923443778,0.07228049786845481,0.05701868743497429,0.061702590441414795,0.027764239702715576,0.03210971062362433,0.07351877806826512,0.04304609921729541,0.03049318734274764,0.033399310824773654,0.027455975786580877,0.05390338010371987,0.04747841575759271,0.029363901310410556,0.03342263940881551,0.09853024119288789,0.02676647175602076,0.03399301791831055,0.045452290270386,0.029192406811105576,0.0666620355357519,0.04840722192861757,0.030786170547362435,0.028343837313798748,0.043072520485650356,0.044332969420804336,0.029937064821125237,0.027155018569014144,0.05484395943600351,0.0351501839931978,0.038505508680795275,0.03066923867657101,0.04483957948679285,0.07121191665734172,0.05455524983914217,0.03835284434467123,0.027612687113610868,0.027134039861746784,0.029456225037923556,0.030184597268272606,0.03873830189441074,0.04567930386787311,0.04198700324265081,0.08410687368718439,0.03351554333468498,0.0293843420708233,0.03651194856495743,0.04114691202504228,0.06278081362849242,0.036249781606069176,0.03983895444856067,0.03986279836797979,0.02722019346264859,0.03806650031208836,0.03798389702093363,0.029032143404262634,0.06010614086240196,0.036009332434605135,0.038898017069831425,0.03676000146717162,0.03174473274591172,0.054184749798626974,0.03068572824192306,0.07704773730802805,0.032977066400182276,0.02670428353615195,0.035014760651571164,0.0608076747731785,0.04064807046923602,0.08847252670177919,0.03932149965190668,0.03350263993257507,0.02932720783012921,0.09849236993652344,0.058851358871576664,0.027105556159394917,0.04689558365528357,0.06054245214317433,0.06885244580745775,0.04099997622689,0.028371408719205737,0.02856989410393651,0.037462354445321866,0.045712409222421035,0.027200085874180546};
    
    // Randomly select a number from the dataset
    float selectedBER = dataset_64[rand() % 530];

    return selectedBER;
}

char* get_enum_name_for_mcs(RANMcsType ran_mcs_enum){
    switch (ran_mcs_enum)
    {
        case RAN_MCS_TYPE__SIXTEEN_QAM:
            return "16-QAM";
        case RAN_MCS_TYPE__SIXTYFOUR_QAM:
            return "64-QAM";
        default:
            return "unrecognized param";
    }
}

/*
 * initialize the ues
 */
void initialize_ues_if_needed(){
    if(is_initialized)
        return;
    for (int ue=0;ue<CONNECTED_UES;ue++){
        connected_ue_list[ue].rnti = rand();
        connected_ue_list[ue].prop_1 = "16-QAM";
        connected_ue_list[ue].prop_2 = -1;
    }
    is_initialized = true;
}

/*
this function has not been implemented and it won't be needed in the foreseeable future
*/
void handle_subscription(RANMessage* in_mess){
    printf("Not implemented\n");
    ran_message__free_unpacked(in_mess,NULL);
    initialize_ues_if_needed();
    assert(0!=0);
}
/*
this function just basically prints out the parameters in the request and passes the in_mess to the response generator
*/
void handle_indication_request(RANMessage* in_mess,int out_socket, sockaddr_in peeraddr){
    initialize_ues_if_needed();
    printf("Indication request for %lu parameters:\n", in_mess->ran_indication_request->n_target_params);
    for(int par_i=0; par_i<in_mess->ran_indication_request->n_target_params; par_i++){
        printf("\tParameter id %d requested (a.k.a %s)\n",\
        in_mess->ran_indication_request->target_params[par_i],\
        get_enum_name(in_mess->ran_indication_request->target_params[par_i]));
    }
    build_indication_response(in_mess, out_socket, peeraddr);
}

/*
this function builds and sends the indication response based on the map inside the in_mess
in_mess is cleared here
*/
void build_indication_response(RANMessage* in_mess, int out_socket, sockaddr_in servaddr){

    RANIndicationResponse rsp = RAN_INDICATION_RESPONSE__INIT;
    RANParamMapEntry **map;
    void* buf;
    unsigned buflen, i;

    // allocate space for the pointers inside the map, which is NULL terminated so it needs 1 additional last pointer
    map = malloc(sizeof(RANParamMapEntry*) * (in_mess->ran_indication_request->n_target_params + 1));

    // now build every element inside the map
    for(i=0; i<in_mess->ran_indication_request->n_target_params; i++){

        // allocate space for this entry and initialize
        map[i] = malloc(sizeof(RANParamMapEntry));
        ran_param_map_entry__init(map[i]);

        // assign key
        map[i]->key=in_mess->ran_indication_request->target_params[i];

        // read the parameter and save it in the map
        ran_read(map[i]->key, map[i]);
    }
    // the map is ready, add the null terminator
    map[in_mess->ran_indication_request->n_target_params] = NULL;

    rsp.n_param_map=in_mess->ran_indication_request->n_target_params;
    rsp.param_map=map;
    buflen = ran_indication_response__get_packed_size(&rsp);
    buf = malloc(buflen);
    ran_indication_response__pack(&rsp,buf);
    printf("Sending indication response\n");
    unsigned slen = sizeof(servaddr);
    int rev = sendto(out_socket, (const char *)buf, buflen,
                     MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                     slen);
    printf("Sent %d bytes, buflen was %u\n",rev, buflen);

    // free map and buffer (rsp not freed because in the stack)
    free_ran_param_map(map);
    free(buf);
    // free incoming ran message
    ran_message__free_unpacked(in_mess,NULL);
}

/*
this function frees a map through introspection, maps !!MUST!! be NULL terminated
*/
void free_ran_param_map(RANParamMapEntry **map){
    int i = 0;
    while(map[i] != NULL){
        // we first need to clear whatever is inside the map entry, we need to consider all the possible value types
        switch(map[i]->value_case){
            case RAN_PARAM_MAP_ENTRY__VALUE_INT64_VALUE:
                // there is no pointer inside the entry to free in this case
                break;
            case RAN_PARAM_MAP_ENTRY__VALUE_STRING_VALUE:
                // free the string and then the entry
                free(map[i]->string_value);
                break;
            case RAN_PARAM_MAP_ENTRY__VALUE_UE_LIST:
                // in this case we free the ue list first
                free_ue_list(map[i]->ue_list);
                break;
            case RAN_PARAM_MAP_ENTRY__VALUE__NOT_SET:
                // nothing to do here, skip to default
            default:
                break;
        }
        // now we can free the entry
        free(map[i]);
        i++;
    }
}

void handle_control(RANMessage* in_mess){
    initialize_ues_if_needed();
    // loop tarhet params and apply
    for(int i=0; i<in_mess->ran_control_request->n_target_param_map; i++){
        printf("Applying target parameter %s with value %s\n",\
        get_enum_name(in_mess->ran_control_request->target_param_map[i]->key),\
        in_mess->ran_control_request->target_param_map[i]->string_value);
        ran_write(in_mess->ran_control_request->target_param_map[i]);
    }
    // free incoming ran message
    ran_message__free_unpacked(in_mess,NULL);
}

const char* get_enum_name(RANParameter ran_par_enum){
    switch (ran_par_enum)
    {
        case RAN_PARAMETER__GNB_ID:
            return "gnb_id";
        case RAN_PARAMETER__UE_LIST:
            return "ue_list";
        default:
            return "unrecognized param";
    }
}

void ran_write(RANParamMapEntry* target_param_map_entry){
    switch (target_param_map_entry->key)
    {
        case RAN_PARAMETER__GNB_ID:
            gnb_id = atoi(target_param_map_entry->string_value);
            break;
        case RAN_PARAMETER__UE_LIST: // if we receive a ue list message we need to apply its content
            apply_properties_to_ue_list(target_param_map_entry->ue_list);
            break;
        default:
            printf("ERROR: cannot write RAN, unrecognized target param %d\n", target_param_map_entry->key);
    }
}

void apply_properties_to_ue_list(UeListM* ue_list){
    // loop the ues and apply what needed to each, according to what is inside the list received from the xapp
    for(int ue=0; ue<ue_list->n_ue_info; ue++){
        // apply generic properties (example)
        set_ue_properties(ue_list->ue_info[ue]->rnti,
                          get_enum_name_for_mcs(ue_list->ue_info[ue]->prop_1),
                          ue_list->ue_info[ue]->prop_2);

        // more stuff later when needed     
    }
}

void set_ue_properties(int rnti, char* prop_1, float prop_2){

    // iterate ue list until rnti is found
    bool rnti_not_found = true;
    for(int ue=0; ue<CONNECTED_UES; ue++) {
        if(connected_ue_list[ue].rnti == rnti){
            printf("RNTI found\n");
            connected_ue_list[ue].prop_1 = prop_1;
            connected_ue_list[ue].prop_2 = prop_2;
            rnti_not_found = false;
            break;
        } else {
            continue;
        }
    }
    if(rnti_not_found){
        printf("RNTI %u not found\n", rnti);
    }
}

char* int_to_charray(int i){
    int length = (snprintf(NULL, 0,"%d",i)+1);
    char* ret = malloc(length*sizeof(char));
    sprintf(ret, "%d", i);
    return ret;
}

void handle_master_message(void* buf, int buflen, int out_socket, struct sockaddr_in servaddr){
    initialize_ues_if_needed();
    RANMessage* in_mess = ran_message__unpack(NULL, (size_t)buflen, buf);
    if (!in_mess){
        printf("Error decoding received message, printing for debug:\n");
        for(int i=0;i<buflen; i++){
            uint8_t* tempbuf = (uint8_t*) buf;
            printf(" %hhx ", tempbuf[i]);
        }
        printf("\n");
        return;
    }
    printf("ran message id %d\n", in_mess->msg_type);
    switch(in_mess->msg_type){
        case RAN_MESSAGE_TYPE__SUBSCRIPTION:
            printf("Subcription message received\n");
            handle_subscription(in_mess);
            break;
        case RAN_MESSAGE_TYPE__INDICATION_REQUEST:
            printf("Indication request message received\n");
            handle_indication_request(in_mess, out_socket, servaddr);
            break;
        case RAN_MESSAGE_TYPE__INDICATION_RESPONSE:
            printf("Indication response message received\n");
            build_indication_response(in_mess, out_socket, servaddr);
            break;
        case RAN_MESSAGE_TYPE__CONTROL:
            printf("Control message received\n");
            handle_control(in_mess);
            break;
        default:
            printf("Unrecognized message type\n");
            ran_message__free_unpacked(in_mess,NULL);
            break;
    }
}


UeListM* build_ue_list_message(){
    // init ue list protobuf message
    UeListM* ue_list_m = malloc(sizeof(UeListM));
    ue_list_m__init(ue_list_m);

    // insert n ues
    ue_list_m->connected_ues = CONNECTED_UES;
    ue_list_m->n_ue_info = CONNECTED_UES;

    // if no ues are connected then we can stop and just return the message
    if(CONNECTED_UES == 0){
        return ue_list_m;
    }
    // build list of ue_info_m (this is also a protobuf message)
    UeInfoM** ue_info_list;
    ue_info_list = malloc(sizeof(UeInfoM*)*(CONNECTED_UES+1)); // allocating space for 1 additional element which will be NULL (terminator element)
    for(int i = 0; i<CONNECTED_UES; i++){
        // init list
        ue_info_list[i] = malloc(sizeof(UeInfoM));
        ue_info_m__init(ue_info_list[i]);

        // read rnti and add to message
        ue_info_list[i]->rnti = connected_ue_list[i].rnti;

        // read mesures and add to message (actually just send random data)

        // measures
        ue_info_list[i]->has_meas_type_1 = 1;
        //ue_info_list[i]->meas_type_1 = rand();
        //ue_info_list[i]->has_meas_type_2 = 1;
        //ue_info_list[i]->meas_type_2 = rand();
        //ue_info_list[i]->has_meas_type_3 = 1;
        //ue_info_list[i]->meas_type_3 = rand();

        if (strcmp(connected_ue_list[i].prop_1, "16-QAM") == 0){
            ue_info_list[i]->meas_type_1 = randomBER16();
        }
        else if (strcmp(connected_ue_list[i].prop_1, "64-QAM") == 0){
            ue_info_list[i]->meas_type_1 = randomBER64();
        }
        else{

        }

        // properties
        ue_info_list[i]->has_prop_1 = 1;
        ue_info_list[i]->prop_1 = connected_ue_list[i].prop_1;
        if(connected_ue_list[i].prop_2 > -1){
        ue_info_list[i]->has_prop_2 = 1;
        ue_info_list[i]->prop_2 = connected_ue_list[i].prop_2;
        }


    }
    // add a null terminator to the list
    ue_info_list[CONNECTED_UES] = NULL;
    // assgin ue info pointer to actually fill the field
    ue_list_m->ue_info = ue_info_list;
    return ue_list_m;
}

// careful, this function leaves dangling pointers - not a big deal in this case though 
void free_ue_list(UeListM* ue_list_m){
    if(ue_list_m->connected_ues > 0){
        // free the ue list content first
        int i=0;
        while(ue_list_m->ue_info[i] != NULL){ // when we reach NULL we have found the terminator (no need to free the terminator because it hasn't been allocated)
            free(ue_list_m->ue_info[i]);
            i++;
        }
        // then free the list
        free(ue_list_m->ue_info);
    }
    // finally free the outer data structure
    free(ue_list_m);
}

void ran_read(RANParameter ran_par_enum, RANParamMapEntry* map_entry){
    switch (ran_par_enum)
    {
        case RAN_PARAMETER__GNB_ID:
            map_entry->value_case=RAN_PARAM_MAP_ENTRY__VALUE_STRING_VALUE;
            map_entry->string_value = int_to_charray(gnb_id);
            break;
        case RAN_PARAMETER__UE_LIST:
            map_entry->value_case=RAN_PARAM_MAP_ENTRY__VALUE_UE_LIST;
            map_entry->ue_list = build_ue_list_message();
            break;
        default:
            printf("Unrecognized param %d\n",ran_par_enum);
            assert(0!=0);
    }
}