/*
*  IntRuleTriangle.cpp
*
*  Created by Leandro Valdez on 4/5/18.
*
*/

#include "IntRuleTriangle.h"
#include "tpanic.h"

/** Symmetric Quadrature rule for triangles from:
Linbo Zhang, Tao Cui and Hui Liu, "A SET OF SYMMETRIC QUADRATURE RULES ON
TRIANGLES AND TETRAHEDRA", J. of Comput. Mathematics, Vol.27, No.1, 2009, 89�96.
*/

/**
In the article it is presented the following table, order versus number of points:
Order:		1	2	3	4	5	6	7	8	9	10
NPoints:	1	3	6	6	7	12	15	16	19	25

Order:		11	12	13	14	15	16	17	18	19	20	21
NPoints:	28	33	37	46	52	55	61	72	73	88	91
*/

#ifdef Length
# undef Length
#endif
#define Length(wts)	(sizeof(wts) / (sizeof(wts[0])))

#define Perm3(a)	a, a, a
#define Dup3(w)		(0.5L*w)
#define Perm21(a)	a, a, 1.L - 2.0L*a, a, 1.L- 2.L*a, a, 1.L- 2.L*a, a, a
#define Dup21(w)	Dup3(w), Dup3(w), Dup3(w)
#define Perm111(a,b)	a, b, 1.L - a - b, a, 1.L - a - b, b, b, a , 1.L - a - b, \
	b, 1.L - a - b, a, 1.L - a - b, a, b, 1.L - a - b, b, a
#define Dup111(w)	Dup3(w), Dup3(w), Dup3(w), Dup3(w), Dup3(w), Dup3(w)

long double QUAD_TRI_P1_wts[] = {
	Dup3(1.L)
};
long double QUAD_TRI_P1_pts[Length(QUAD_TRI_P1_wts) * 3] = {
	Perm3(1.L / 3.L)
};

long double QUAD_TRI_P2_wts[] = {
	Dup21(1.L / 3.L)
};
long double QUAD_TRI_P2_pts[Length(QUAD_TRI_P2_wts) * 3] = {
	Perm21(1.L / 6.L)
};

long double QUAD_TRI_P3_wts[] = {
	Dup21(.28114980244097964825351432270207695L),
	Dup21(.05218353089235368507981901063125638L)
};
long double QUAD_TRI_P3_pts[Length(QUAD_TRI_P3_wts) * 3] = {
	Perm21(.16288285039589191090016180418490635L),
	Perm21(.47791988356756370000000000000000000L)
};

long double QUAD_TRI_P4_wts[] = {
	/* (620 + sqrt(213125 - 53320 * sqrt(10))) / 3720 */
	Dup21(.22338158967801146569500700843312280L),
	/* (620 - sqrt(213125 - 53320 * sqrt(10))) / 3720 */
	Dup21(.10995174365532186763832632490021053L)
};
long double QUAD_TRI_P4_pts[Length(QUAD_TRI_P4_wts) * 3] = {
	/* (8 - sqrt(10) + sqrt(38 - 44 * sqrt(2 / 5))) / 18 */
	Perm21(.44594849091596488631832925388305199L),
	/* (8 - sqrt(10) - sqrt(38 - 44 * sqrt(2 / 5))) / 18 */
	Perm21(.09157621350977074345957146340220151L)
};

long double QUAD_TRI_P5_wts[] = {
	/* (155 - sqrt(15)) / 1200 */
	Dup21(.12593918054482715259568394550018133L),
	/* (155 + sqrt(15)) / 1200 */
	Dup21(.13239415278850618073764938783315200L),
	Dup3(9.L / 40.L)
};
long double QUAD_TRI_P5_pts[Length(QUAD_TRI_P5_wts) * 3] = {
	/* (6 - sqrt(15)) / 21 */
	Perm21(.10128650732345633880098736191512383L),
	/* (6 + sqrt(15)) / 21 */
	Perm21(.47014206410511508977044120951344760L),
	/* 1 / 3 */
	Perm3(1.L / 3.L)
};


/* Note: an 11-point rule has been found in:
*	 Day, David M., Mark A. Taylor, "A new 11 point degree 6 cubature
*	 	formula for the triangle [Proceedings of the ICIAM 2007],"
*	 Journal Article, Proceedings of Applied Mathematics and Mechanics,
*	 Accepted/Published January 2008. */
long double QUAD_TRI_P6_wts[] = {
	Dup21(.05084490637020681692093680910686898L),
	Dup21(.11678627572637936602528961138557944L),
	Dup111(.08285107561837357519355345642044245L)
};
long double QUAD_TRI_P6_pts[Length(QUAD_TRI_P6_wts) * 3] = {
	Perm21(.06308901449150222834033160287081916L),
	Perm21(.24928674517091042129163855310701908L),
	Perm111(.05314504984481694735324967163139815L,
	.31035245103378440541660773395655215L)
};

long double QUAD_TRI_P7_wts[] = {
	Dup21(.01353386251566556156682309245259393L),
	Dup21(.07895125443201098137652145029770332L),
	Dup21(.12860792781890607455665553308952344L),
	Dup111(.05612014428337535791666662874675632L)
};
long double QUAD_TRI_P7_pts[Length(QUAD_TRI_P7_wts) * 3] = {
	Perm21(.02826392415607634022359600691324002L),
	Perm21(.47431132326722257527522522793181654L),
	Perm21(.24114332584984881025414351267036207L),
	Perm111(.76122274802452380000000000000000000L,
	.04627087779880891064092559391702049L)
};

long double QUAD_TRI_P8_wts[] = {
	Dup3(.14431560767778716825109111048906462L),
	Dup21(.10321737053471825028179155029212903L),
	Dup21(.03245849762319808031092592834178060L),
	Dup21(.09509163426728462479389610438858432L),
	Dup111(.02723031417443499426484469007390892L)
};
long double QUAD_TRI_P8_pts[Length(QUAD_TRI_P8_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.17056930775176020662229350149146450L),
	Perm21(.05054722831703097545842355059659895L),
	Perm21(.45929258829272315602881551449416932L),
	Perm111(.26311282963463811342178578628464359L,
	.00839477740995760533721383453929445L)
};

long double QUAD_TRI_P9_wts[] = {
	Dup3(.09713579628279883381924198250728863L),
	Dup21(.03133470022713907053685483128720932L),
	Dup21(.02557767565869803126167879855899982L),
	Dup21(.07782754100477427931673935629940396L),
	Dup21(.07964773892721025303289177426404527L),
	Dup111(.04328353937728937728937728937728938L)
};
long double QUAD_TRI_P9_pts[Length(QUAD_TRI_P9_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.48968251919873762778370692483619280L),
	Perm21(.04472951339445270986510658996627636L),
	Perm21(.43708959149293663726993036443535497L),
	Perm21(.18820353561903273024096128046733557L),
	Perm111(.74119859878449802069007987352342383L,
	.22196298916076569567510252769319107L)
};

long double QUAD_TRI_P10_wts[] = {
	Dup3(.08093742879762288025711312381650193L),
	Dup21(.07729858800296312168250698238034344L),
	Dup21(.07845763861237173136809392083439673L),
	Dup21(.01746916799592948691760716329067815L),
	Dup21(.00429237418483282803048040209013191L),
	Dup111(.03746885821046764297902076548504452L),
	Dup111(.02694935259187995964544947958109671L)
};
long double QUAD_TRI_P10_pts[Length(QUAD_TRI_P10_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.42727317884677553809044271751544715L),
	Perm21(.18309922244867502052157438485022004L),
	Perm21(.49043401970113058745397122237684843L),
	Perm21(.01257244555158053273132908502104126L),
	Perm111(.65426866792006614066657009558762790L,
	.30804600168524770000000000000000000L),
	Perm111(.12280457706855927343012981748128116L,
	.03337183373930478624081644177478038L)
};

long double QUAD_TRI_P11_wts[] = {
	Dup3(.08117796029686715951547596874982357L),
	Dup21(.01232404350690949411847390101623284L),
	Dup21(.06282800974441010728333942816029398L),
	Dup21(.01222037904936452975521221500393789L),
	Dup21(.06770134895281150992098886182322559L),
	Dup21(.04021969362885169042356688960756866L),
	Dup111(.01476227271771610133629306558778206L),
	Dup111(.04072799645829903966033695848161786L)
};
long double QUAD_TRI_P11_pts[Length(QUAD_TRI_P11_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.03093835524543078489519501499130475L),
	Perm21(.43649818113412884191761527655997324L),
	Perm21(.49898476370259326628798698383139087L),
	Perm21(.21468819795859433660687581387825086L),
	Perm21(.11368310404211339020529315622836178L),
	Perm111(.82561876616486290435880620030835800L,
	.15974230459185018980086078822500751L),
	Perm111(.64047231013486526767703659081896681L,
	.31178371570959900000000000000000000L)
};

long double QUAD_TRI_P12_wts[] = {
	Dup21(.00616626105155901723386648378523035L),
	Dup21(.06285822421788510035427051309288255L),
	Dup21(.03479611293070894298932839729499937L),
	Dup21(.04369254453803840213545726255747497L),
	Dup21(.02573106644045533541779092307156443L),
	Dup111(.02235677320230344571183907670231999L),
	Dup111(.01731623110865889237164210081103407L),
	Dup111(.04037155776638092951782869925223677L)
};
long double QUAD_TRI_P12_pts[Length(QUAD_TRI_P12_wts) * 3] = {
	Perm21(.02131735045321037024685697551572825L),
	Perm21(.27121038501211592234595134039689474L),
	Perm21(.12757614554158592467389632515428357L),
	Perm21(.43972439229446027297973662348436108L),
	Perm21(.48821738977380488256466206525881104L),
	Perm111(.69583608678780342214163552323607254L,
	.28132558098993954824813069297455275L),
	Perm111(.85801403354407263059053661662617818L,
	.11625191590759714124135414784260182L),
	Perm111(.60894323577978780685619243776371007L,
	.27571326968551419397479634607976398L)
};

long double QUAD_TRI_P13_wts[] = {
	Dup3(.06796003658683164428177442468088488L),
	Dup21(.05560196753045332870725746601046147L),
	Dup21(.05827848511919998140476708351333981L),
	Dup21(.00605233710353917184179280003229082L),
	Dup21(.02399440192889473077371079945095965L),
	Dup111(.03464127614084837046598682851091822L),
	Dup111(.01496540110516566726324585713290344L),
	Dup111(.02417903981159381913744574557306076L),
	Dup111(.00959068100354326272259509016611089L)
};
long double QUAD_TRI_P13_pts[Length(QUAD_TRI_P13_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.42694141425980040602081253503137421L),
	Perm21(.22137228629183290065481255470507908L),
	Perm21(.02150968110884318386929131353405208L),
	Perm21(.48907694645253934990068971909020439L),
	Perm111(.62354599555367557081585435318623659L,
	.30844176089211777465847185254124531L),
	Perm111(.86470777029544277530254595089569318L,
	.11092204280346339541286954522167452L),
	Perm111(.74850711589995219517301859578870965L,
	.16359740106785048023388790171095725L),
	Perm111(.72235779312418796526062013230478405L,
	.27251581777342966618005046435408685L)
};

long double QUAD_TRI_P14_wts[] = {
	Dup3(.05859628522602859412789380634775601L),
	Dup21(.00173515122972526756806186388080941L),
	Dup21(.02616378255861452177782885918197827L),
	Dup21(.00391972924240182909652082757014540L),
	Dup21(.01224735975694086609728698992625048L),
	Dup21(.02819962850325796010736630715156571L),
	Dup21(.05088708718595948529603482754545404L),
	Dup21(.05045343990160359919102089713411889L),
	Dup111(.01706364421223345129002539938494722L),
	Dup111(.00968346642550660040752096309341938L),
	Dup111(.03638575592848500562201132776427165L),
	Dup111(.00696466337351841242539972250424131L)
};
long double QUAD_TRI_P14_pts[Length(QUAD_TRI_P14_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.00997976080645843241529352958205243L),
	Perm21(.47997789352118838981055286508838991L),
	Perm21(.15381195917696690000000000000000000L),
	Perm21(.07402347711698781000000000000000000L),
	Perm21(.13035468250333000000000000000000000L),
	Perm21(.23061722602665313429960537009838312L),
	Perm21(.42233208341914782411440871379139388L),
	Perm111(.78623738593466100332962211403309001L,
	.19061636003190090424614328286530343L),
	Perm111(.63055214366060744162240907556881292L,
	.36232313774354714461832673435977294L),
	Perm111(.62657732985630631423351231375342650L,
	.29077120588366741502481681748167319L),
	Perm111(.91420998492962541223996709938504695L,
	.07116571087775076254759245029243364L)
};

long double QUAD_TRI_P15_wts[] = {
	Dup3(.04403871087843427985301732721493388L),
	Dup21(.04618478718202697994871566760191669L),
	Dup21(.00649890661733271652688280349281019L),
	Dup21(.01799361425265840324466992416715655L),
	Dup21(.04177310503914135411968606056414597L),
	Dup21(.00305954760911646654843016992834484L),
	Dup21(.00201243505255864734409031875654046L),
	Dup21(.01677561093050912232611145688795876L),
	Dup111(.01546074918971427486608803040924742L),
	Dup111(.02849989033954742339273955875330195L),
	Dup111(.03209435048348959564209923573709566L),
	Dup111(.01150858163687071128402324377324186L),
	Dup111(.00461430652896710314358717609185406L)
};
long double QUAD_TRI_P15_pts[Length(QUAD_TRI_P15_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.22733221881914287420250436849229406L),
	Perm21(.49716257743188742987380980001602329L),
	Perm21(.47884973534895458333922920014385258L),
	Perm21(.40498603909827199169724464234269204L),
	Perm21(.01593121667174443211342773294126896L),
	Perm21(.16558326242608140000000000000000000L),
	Perm21(.07313360471922872772687381210732441L),
	Perm111(.66526073307221393906236441338569119L,
	.31635283934494723008633813095024529L),
	Perm111(.71252198724254553304884901162338783L,
	.09346075114991753000000000000000047L),
	Perm111(.55964836223539321841224845401923000L,
	.34422901758219320000000000000000160L),
	Perm111(.81047659761907686304683273029057126L,
	.17104724831425795154765033192558481L),
	Perm111(.91607564403173118856460883877832000L,
	.07305599647918648961294908192742498L)
};

long double QUAD_TRI_P16_wts[] = {
	Dup3(.04802218868037709055183940458051988L),
	Dup21(.01470910030680192710340364286186919L),
	Dup21(.02954458654931925599530972679646409L),
	Dup21(.02612501735108837749859756549171557L),
	Dup21(.00278038735239000697500301613866207L),
	Dup21(.03182177300053664950342729005594961L),
	Dup21(.00864583434950965990117373416984893L),
	Dup111(.01430033290449536514661642536825213L),
	Dup111(.02784977720360082995222987342395349L),
	Dup111(.00704167340663609756237018808928069L),
	Dup111(.01789983825993372860177020907581078L),
	Dup111(.02745820038434976307247003810091720L),
	Dup111(.00729979693943176208411254408777766L)
};
long double QUAD_TRI_P16_pts[Length(QUAD_TRI_P16_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.08179498313137387264146559311886101L),
	Perm21(.16530060196977965062676193293355656L),
	Perm21(.46859210534946138669460289729660561L),
	Perm21(.01443881344541668261410895669566020L),
	Perm21(.24178428539178335340689445929320769L),
	Perm21(.49531034298776996406549508687740551L),
	Perm111(.65051340266135229943114468484168666L,
	.33139974453708955658132316818259388L),
	Perm111(.60401128149599703984940410303596702L,
	.30324716274994218504155217807834692L),
	Perm111(.80216825757474166361686194781166705L,
	.18802805952123717344418211429398875L),
	Perm111(.75650560644282839655115407575806082L,
	.18350466852229686368238027743700035L),
	Perm111(.46593843871411818488381073359154639L,
	.35964594879750460000000000000001000L),
	Perm111(.90639484399204150136249966186534000L,
	.07719437129575543228251522505271386L)
};

long double QUAD_TRI_P17_wts[] = {
	Dup3(.04475687144434462937183647670425513L),
	Dup21(.01736688502674779645049111764776038L),
	Dup21(.03059934807610353272266564726895704L),
	Dup21(.02858770857859978020704009121768920L),
	Dup21(.00664743192975369323231849554546676L),
	Dup21(.00747618940201851182224557347080098L),
	Dup21(.02504998650383874531455895190550778L),
	Dup111(.00147981089211964494480953682750477L),
	Dup111(.00512113624674810606589435040573260L),
	Dup111(.02731735936959280591853168984239567L),
	Dup111(.01400572867590928159786633211401179L),
	Dup111(.00780927569745836009810987323288001L),
	Dup111(.01816572845979167217607207751722372L),
	Dup111(.02744437399245832776208345541478450L)
};
long double QUAD_TRI_P17_pts[Length(QUAD_TRI_P17_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.09569850886271093994316257860237634L),
	Perm21(.17013863967877544672324723079568443L),
	Perm21(.41802068586795497622263464239342782L),
	Perm21(.49658148050662495497054035306227918L),
	Perm21(.04166211482880764279207885159834192L),
	Perm21(.46793290572942357826819008536171190L),
	Perm111(.96953119890372205619454058305953242L,
	.02892509162021824607152804771406821L),
	Perm111(.75972438753862412955532719532266120L,
	.23444175526356877454266053091297880L),
	Perm111(.29549931696830150000000000000001000L,
	.49591124666075357542303450004375516L),
	Perm111(.62560638215769702707019209266693705L,
	.35341769454149706762632499077099377L),
	Perm111(.87217444723318479290318300141560742L,
	.11272864181421976861888886768074196L),
	Perm111(.74751231944000604006240678176087530L,
	.19907027879785788131339143981558306L),
	Perm111(.59886879088323805980616769726351095L,
	.30358518307132607653202051204584937L)
};

long double QUAD_TRI_P18_wts[] = {
	Dup21(.01397786164528602097958400799055493L),
	Dup21(.00055490697921321378506845551525090L),
	Dup21(.02102681381970466902842986851624498L),
	Dup21(.03401821217992769974722652741822109L),
	Dup111(.02791016580477499514184347400781694L),
	Dup111(.01821468612715086612673395662068577L),
	Dup111(.01426702365810979307751982410955666L),
	Dup111(.01423712309067505070431276377415596L),
	Dup111(.01925758385467478779913738368202133L),
	Dup111(.00970513228438064114878227633239023L),
	Dup111(.00762978813433212899578245563385336L),
	Dup111(.01061873913635034479446354367052828L),
	Dup111(.00571066980327583881341421438268949L),
	Dup111(.00432685746087641829452234473283270L)
};
long double QUAD_TRI_P18_pts[Length(QUAD_TRI_P18_wts) * 3] = {
	Perm21(.07327088646438283157861967148768954L),
	Perm21(.00391774898322823164278407441958060L),
	Perm21(.46759731898871106165151299662296245L),
	Perm21(.41791621096741131201212681051399350L),
	Perm111(.16538169336028948005449026923917662L,
	.56369670566087075380514589393807372L),
	Perm111(.28750089440578398999619391313966060L,
	.28604232613920474912095810748030295L),
	Perm111(.12588931431982479601706483994903803L,
	.69604321864246119579257486028195390L),
	Perm111(.06322191594650261449357508011699804L,
	.76054555188768243261459476379786871L),
	Perm111(.07891022745402051775207221037548892L,
	.59201963127175856332262057540222541L),
	Perm111(.03805805350678571432611899159626213L,
	.68368125963599985248012408745381310L),
	Perm111(.01429035213045402564992411031307492L,
	.85170403713705581502852165344276639L),
	Perm111(.01296727234325317231234163433009032L,
	.57473249288814902889945093868968971L),
	Perm111(.00764859482084089933079262881822729L,
	.73551044083072929870313522448164061L),
	Perm111(.01271046057225546793114249181358220L,
	.93934508764373178870740420268282255L)
};

/* Note: the rule QUAD_TRI_P19 was taken from the book by
*	P. Solin, K. Segeth, and I. Dolezel,
*	"Higer-order Finite Element Methods",
*	Chapman and Hall/CRC Press, 2003. */
long double QUAD_TRI_P19_wts[] = {
	Dup3(.03290633138891865208361434484647497L),
	Dup21(.01033073189127205336703996357174833L),
	Dup21(.02238724726301639252918455603516271L),
	Dup21(.03026612586946807086528019098259122L),
	Dup21(.03049096780219778100003158657852042L),
	Dup21(.02415921274164090491184803098664001L),
	Dup21(.01605080358680087529162277027642948L),
	Dup21(.00808458026178406048180567324219442L),
	Dup21(.00207936202748478075134750167439841L),
	Dup111(.00388487690498138975670499199277266L),
	Dup111(.02557416061202190389292970195260027L),
	Dup111(.00888090357333805774552592470351753L),
	Dup111(.01612454676173139121978526932783766L),
	Dup111(.00249194181749067544058464757594956L),
	Dup111(.01824284011895057837766571320973615L),
	Dup111(.01025856373619852130804807004235813L),
	Dup111(.00379992885530191397907315371363970L)
};
long double QUAD_TRI_P19_pts[Length(QUAD_TRI_P19_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.48960998707300633196613106574829817L),
	Perm21(.45453689269789266204675939053572830L),
	Perm21(.40141668064943118739399562381068860L),
	Perm21(.25555165440309761132218176810926787L),
	Perm21(.17707794215212955164267520651590115L),
	Perm21(.11006105322795186130008495167737397L),
	Perm21(.05552862425183967124867841247135571L),
	Perm21(.01262186377722866849023476677870599L),
	Perm111(.60063379479464500000000000000000000L,
	.39575478735694286230479469406582787L),
	Perm111(.13446675453077978561204319893264695L,
	.55760326158878396836395324250118097L),
	Perm111(.72098702581736505521665290233827892L,
	.26456694840652020804030173490121494L),
	Perm111(.59452706895587092461388928802650670L,
	.35853935220595058842492699064590088L),
	Perm111(.83933147368083857861749007714840520L,
	.15780740596859474473767360335950651L),
	Perm111(.22386142409791569130336938950653642L,
	.70108797892617336732328833655951158L),
	Perm111(.82293132406985663162747155916053316L,
	.14242160111338343731557475687723745L),
	Perm111(.92434425262078402945585913790156314L,
	.06549462808293770339232652498592557L)
};

long double QUAD_TRI_P20_wts[] = {
	Dup3(.01253760799449665657358563677239480L),
	Dup21(.02747186987642421374845354960735985L),
	Dup21(.00976527227705142304136469142942368L),
	Dup21(.00139841953539182352392336315978673L),
	Dup21(.00929210262518518263042820340303303L),
	Dup21(.01657787603236692532602362503518398L),
	Dup111(.02066776234866507696142197001297288L),
	Dup111(.02082223552115450730687855619932975L),
	Dup111(.00956863841984906068887584504583203L),
	Dup111(.02445277096897246388564392070240889L),
	Dup111(.00315573063063053400382640032072957L),
	Dup111(.01213679636532129693701330908075738L),
	Dup111(.01496648014388644903652491185157070L),
	Dup111(.00632759332177773956932403275043979L),
	Dup111(.00134256031206369588497985129814333L),
	Dup111(.00277607691634755406772935615580153L),
	Dup111(.01073984447418494155517344744795167L),
	Dup111(.00536780573818745320524741002126972L)
};
long double QUAD_TRI_P20_pts[Length(QUAD_TRI_P20_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.21587430593299197319025454384018276L),
	Perm21(.07537676652974727809728543094591628L),
	Perm21(.01030082813722179211368621600969694L),
	Perm21(.49360221129870016551192083214505357L),
	Perm21(.46155093810692529674104871029151803L),
	Perm111(.32862140642423699330349746095091325L,
	.42934057025821037521395880046639840L),
	Perm111(.26048036178656875641959301708115346L,
	.10157753428096944616875500619617966L),
	Perm111(.13707423584645530000000000000000000L,
	.71006597300113015998790407454640790L),
	Perm111(.14672694587229978430416098848745303L,
	.49854547767841484938962269670761193L),
	Perm111(.02699897774255329000000000000000000L,
	.04918672267258200161970371257758717L),
	Perm111(.06187178593361702684171247001223384L,
	.77966014654056939536035061907681080L),
	Perm111(.04772436742762199620835268010429344L,
	.37049153914954763692014962025673877L),
	Perm111(.12060051518636437996723378704007933L,
	.86334694875475264849798799609252174L),
	Perm111(.00269714779670978767164891450128273L,
	.05619493818774550298789230198658868L),
	Perm111(.00301563327794236265727625982347101L,
	.20867500674842135095759446306135771L),
	Perm111(.02990537578845701880692877386433865L,
	.72115124091203409102810415020509411L),
	Perm111(.00675665422246098853994581751922784L,
	.64005544194054188990405366827216467L)
};

long double QUAD_TRI_P21_wts[] = {
	Dup3(.02756225695287648096690704482451431L),
	Dup21(.02206021541348850119135073403311636L),
	Dup21(.02346001593867148849301344495230002L),
	Dup21(.00032688959504719054621455750154654L),
	Dup21(.00326531946293996823433530409586668L),
	Dup21(.01175646291541279770430796921338205L),
	Dup21(.01178076841991151684555757909867614L),
	Dup111(.00226881081880114080533570433430431L),
	Dup111(.00259601096443632006067378366548822L),
	Dup111(.00463452978587186021234789056159687L),
	Dup111(.00479433605454885793485744871991192L),
	Dup111(.00571247883672361156725063834296336L),
	Dup111(.00586582760432212163695579870000227L),
	Dup111(.00941376305909158758981826852034708L),
	Dup111(.01341494379665642491002202661089309L),
	Dup111(.01571691809208324594350000113784617L),
	Dup111(.01686368301443690459165096388619991L),
	Dup111(.02139002708532009837783229808035898L),
	Dup111(.02307679218949268136788087552189154L)
};
long double QUAD_TRI_P21_pts[Length(QUAD_TRI_P21_wts) * 3] = {
	Perm3(.33333333333333333333333333333333333L),
	Perm21(.20093527706508527987296185156416367L),
	Perm21(.43765916596192717973183384418805413L),
	Perm21(.00343395649059617685095991220960492L),
	Perm21(.04664348477530675349517624043214192L),
	Perm21(.38642225176307149094035202416772642L),
	Perm21(.09543547110853091010857168104147605L),
	Perm111(.95551380335045636050131472514677118L,
	.03571862787316335823804160897543867L),
	Perm111(.88663881342886822612490057469143760L,
	.10814322491564621152738861104631270L),
	Perm111(.78426284588043415429664399039819537L,
	.20746444959987645682438042951572740L),
	Perm111(.88292395505020003271134898731688967L,
	.08568470872031694000000000000001000L),
	Perm111(.66899196444107724049132248320989459L,
	.32149400301428881688168321268348603L),
	Perm111(.55207212103556096415716096525277878L,
	.43794221879334138355236807696291701L),
	Perm111(.79759296559656856762931422329572582L,
	.16191645306357785675100677020385905L),
	Perm111(.67751471511977148463499116634413256L,
	.27450476740199490385900297290733317L),
	Perm111(.54299741558909160533113611683919342L,
	.40533599807500692794989089537632556L),
	Perm111(.70545990556996856165885634154060172L,
	.18773768065643534277281674394512005L),
	Perm111(.57480057306650846221598245054985001L,
	.30569683476605516651279255664984316L),
	Perm111(.47177880850461481660397704013492420L,
	.31214446687089088167080460581557645L)
};

IntRuleTriangle::IntRuleTriangle() :IntRule() {}

IntRuleTriangle::IntRuleTriangle(int order)
{
	SetOrder(order);

	// Define o n�mero de pontos necess�rios para integra��o
	int NRGAUPO[22] = { 1, 1, 3, 6, 6, 7, 12, 15, 16, 19, 25, 28, 33, 37, 46, 52, 55, 61, 72, 73, 88, 91 };
	int npoints = NRGAUPO[fOrder];

	fPoints.Resize(npoints, 2);
	fWeights.resize(npoints);

	////Calcula os pontos e pesos b�sicos
	switch (fOrder) {
	case 0:
	case 1:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P1_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P1_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 2:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P2_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P2_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 3:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P3_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P3_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 4:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P4_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P4_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 5:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P5_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P5_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 6:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P6_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P6_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 7:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P7_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P7_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 8:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P8_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P8_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 9:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P9_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P9_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 10:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P10_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P10_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 11:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P11_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P11_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 12:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P12_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P12_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 13:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P13_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P13_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 14:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P14_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P14_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 15:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P15_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P15_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 16:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P16_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P16_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 17:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P17_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P17_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 18:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P18_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P18_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 19:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P19_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P19_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 20:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P20_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P20_pts[3 * i + (j + 1)];
			}
		}
		break;
	case 21:
		for (int i = 0; i<npoints; i++) {
			fWeights[i] = QUAD_TRI_P21_wts[i];
			for (int j = 0; j < fPoints.Cols(); j++)
			{
				fPoints(i, j) = QUAD_TRI_P21_pts[3 * i + (j + 1)];
			}
		}
		break;
	default:
		DebugStop();
	}
}

void IntRuleTriangle::SetOrder(int order)
{
	if (order < 0 || order > 21)
	{
		DebugStop();
	}

	fOrder = order;
}