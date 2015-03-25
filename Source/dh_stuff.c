/* dh_stuff.c			*/
/* Support for dehacker scripts	*/
/* Written by J.A.Doggett	*/
/* Copyright 1998		*/

#include "includes.h"

/* Strings from info.c */
extern char * sprnames [];
extern char * sprnames_orig[];

/* Strings from f_finale.c */
extern char*	finale_messages[];
extern char*	finale_messages_orig[];
extern char*	finale_backdrops[];
extern char*	finale_backdrops_orig[];
extern char*	cast_names_copy[];
extern castinfo_t castorder[];
extern clusterdefs_t * finale_clusterdefs;

/* Structs from p_enemy.c */
extern bossdeath_t boss_death_table[];
extern bossdeath_t * boss_death_table_2;

/* Strings from p_inter.c */
extern char * got_messages [];
extern char * got_messages_orig [];
extern char * obituary_messages [];

/* Strings from d_main.c */
extern char * dmain_messages [];
extern char * dmain_messages_orig [];
extern char * startup_messages [];

/* Strings from m_menu.c */
extern char * menu_messages [];
extern char * menu_messages_orig [];
extern char * episode_names [];
extern char * endmsg [];
extern char * endmsg_orig [];
extern int qty_endmsg_nums;

/* Strings from p_doors.c */
extern char * door_messages [];
extern char * door_messages_orig [];

/* Strings from g_game.c */
extern char * save_game_messages [];
extern char * save_game_messages_orig [];

extern const char sky_1 [];
extern const char sky_2 [];
extern const char sky_3 [];
extern const char sky_4 [];
extern const char cwilv [];
extern const char wilv [];
extern const char enterpic_1 [];
extern const char enterpic_2 [];
extern const char borderpatch_1 [];
extern const char borderpatch_2 [];

/* Strings from am_map.c */
extern char * am_map_messages [];
extern char * am_map_messages_orig [];
extern unsigned char cheat_amap_seq[];

/* Strings from hu_stuff.c */
extern char* chat_macros[];
extern char* chat_macros_orig[];
extern char* player_names[];
extern char* player_names_orig[];

/* Strings from st_stuff.c */
extern char * stat_bar_messages [];
extern char * stat_bar_messages_orig [];
extern unsigned char	cheat_mus_seq[];
extern unsigned char	cheat_choppers_seq[];
extern unsigned char	cheat_god_seq[];
extern unsigned char	cheat_ammo_seq[];
extern unsigned char	cheat_ammonokey_seq[];
extern unsigned char	cheat_noclip_seq[];
extern unsigned char	cheat_commercial_noclip_seq[];
extern unsigned char	cheat_powerup_seq[7][10];
extern unsigned char	cheat_clev_seq[];
extern unsigned char	cheat_mypos_seq[];

/* Variables from st_stuff.c */
extern unsigned int God_Mode_Health;
extern unsigned int IDFA_Armour;
extern unsigned int IDFA_Armour_Class;
extern unsigned int IDKFA_Armour;
extern unsigned int IDKFA_Armour_Class;

/* Strings from p_spec.c */
extern char * special_effects_messages [];
extern char * special_effects_messages_orig [];

/* Strings from sounds.c */
extern char * music_names_copy [];
extern char * sound_names_copy [];

/* Variables from g_game.c */
extern unsigned int Initial_Health;
extern unsigned int Initial_Bullets;

/* Variables from p_inter.c */
extern unsigned int Max_Health_100;
extern unsigned int Max_Health_200;
extern unsigned int Max_Armour;
extern unsigned int Max_Soulsphere_Health;
extern unsigned int Soulsphere_Health;
extern unsigned int Megasphere_Health;
extern unsigned int Green_Armour_Class;
extern unsigned int Blue_Armour_Class;
extern int	maxammo[];
extern int	clipammo[];

/* Variables from p_pspr.c */
extern unsigned int bfg_cells;

/* Variables from p_map.c */
extern boolean Monsters_Infight1;

unsigned int Player_Jump = 0;
unsigned int Homing_Missiles = 0;

boolean  finale_message_changed = false;
boolean	 dh_changing_pwad = false;

//extern map_dests_t * G_Access_MapInfoTab_E (unsigned int episode, unsigned int map);
// static void DH_DetectPwads (void);

/* ---------------------------------------------------------------------------- */

/* Put some pointers in for DeHackEd to follow */
/* Doesn't work as the compiler puts them in the data segment */
/* rather than the code segment. */
#ifdef __riscos_NOT

static mobjinfo_t const * const ThingTableOffset = &mobjinfo[0];
static const int SoundNameTableOffset = 0;
static const int SoundDetailsOffset = 0;
static const int SpriteNameTableOffset = 0;
static const unsigned char * CheatTableOffset = &cheat_powerup_seq[0][0];
static const state_t	* FrameTableOffset = &states[0];
static const weaponinfo_t * WeaponTableOffset = &weaponinfo[0];
static const int * AmmoTableOffset = &maxammo [0];

#endif

/* ---------------------------------------------------------------------------- */
// Doesn't work with g++, needs actionf_p1
extern void A_Light0(void *);
extern void A_WeaponReady(void *);
extern void A_Lower(void *);
extern void A_Raise(void *);
extern void A_Punch(void *);
extern void A_ReFire(void *);
extern void A_FirePistol(void *);
extern void A_Light1(void *);
extern void A_FireShotgun(void *);
extern void A_Light2(void *);
extern void A_FireShotgun2(void *);
extern void A_CheckReload(void *);
extern void A_OpenShotgun2(void *);
extern void A_LoadShotgun2(void *);
extern void A_CloseShotgun2(void *);
extern void A_FireCGun(void *);
extern void A_GunFlash(void *);
extern void A_FireMissile(void *);
extern void A_Saw(void *);
extern void A_FirePlasma(void *);
extern void A_BFGsound(void *);
extern void A_FireBFG(void *);
extern void A_BFGSpray(void *);
extern void A_Explode(void *);
extern void A_Pain(void *);
extern void A_PlayerScream(void *);
extern void A_Fall(void *);
extern void A_XScream(void *);
extern void A_Look(void *);
extern void A_Chase(void *);
extern void A_FaceTarget(void *);
extern void A_PosAttack(void *);
extern void A_Scream(void *);
extern void A_SPosAttack(void *);
extern void A_VileChase(void *);
extern void A_VileStart(void *);
extern void A_VileTarget(void *);
extern void A_VileAttack(void *);
extern void A_StartFire(void *);
extern void A_Fire(void *);
extern void A_FireCrackle(void *);
extern void A_Tracer(void *);
extern void A_SkelWhoosh(void *);
extern void A_SkelFist(void *);
extern void A_SkelMissile(void *);
extern void A_FatRaise(void *);
extern void A_FatAttack1(void *);
extern void A_FatAttack2(void *);
extern void A_FatAttack3(void *);
extern void A_BossDeath(void *);
extern void A_CPosAttack(void *);
extern void A_CPosRefire(void *);
extern void A_TroopAttack(void *);
extern void A_SargAttack(void *);
extern void A_HeadAttack(void *);
extern void A_BruisAttack(void *);
extern void A_SkullAttack(void *);
extern void A_Metal(void *);
extern void A_SpidRefire(void *);
extern void A_BabyMetal(void *);
extern void A_BspiAttack(void *);
extern void A_Hoof(void *);
extern void A_CyberAttack(void *);
extern void A_PainAttack(void *);
extern void A_PainDie(void *);
extern void A_KeenDie(void *);
extern void A_BrainPain(void *);
extern void A_BrainScream(void *);
extern void A_BrainDie(void *);
extern void A_BrainAwake(void *);
extern void A_BrainSpit(void *);
extern void A_SpawnSound(void *);
extern void A_SpawnFly(void *);
extern void A_BrainExplode(void *);
extern void P_Massacre (void);

/* ---------------------------------------------------------------------------- */

typedef enum
{
  JOB_NULL,
  JOB_THING,
  JOB_SOUND,
  JOB_FRAME,
  JOB_SPRITE,
  JOB_AMMO,
  JOB_WEAPON,
  JOB_POINTER,
  JOB_CHEAT,
  JOB_MISC,
  JOB_TEXT,
  JOB_PARS,
  JOB_CODEPTR,
  JOB_STRINGS,
  JOB_END,
  QTY_JOBS
} dhjobs_t;

/* ---------------------------------------------------------------------------- */

static const char * const dehack_patches [] =
{
  "Patch File",
  "Thing",
  "Sound",
  "Frame",
  "Sprite",
  "Ammo",
  "Weapon",
  "Pointer",
  "Cheat",
  "Misc",
  "Text",
  "[PARS]",
  "[CODEPTR]",
  "[STRINGS]",
  "[END]",
  NULL
};

#if 0
static const char * const dehack_info [] =
{
  "Doom version",
  "Patch format",
  NULL
};
#endif

static const char * const dehack_things [] =
{
  "ID #",
  "Initial frame",
  "Hit points",
  "First moving frame",
  "Alert sound",
  "Reaction time",
  "Attack sound",
  "Injury frame",
  "Pain chance",
  "Pain sound",
  "Close attack frame",
  "Far attack frame",
  "Death frame",
  "Exploding frame",
  "Death sound",
  "Speed",
  "Width",
  "Height",
  "Mass",
  "Missile damage",
  "Action sound",
  "Bits",
  "Respawn frame",
  "Scale",
  NULL
};


static const char * const dehack_sounds [] =
{
  "Offset",
  "Zero/One",
  "Value",
  "Zero 1",
  "Zero 2",
  "Zero 3",
  "Zero 4",
  "Neg. One 1",
  "Neg. One 2",
  NULL
};

static const char * const dehack_sprites [] =
{
  "Offset",
  NULL
};

static const char * const dehack_frames [] =
{
  "Sprite number",
  "Sprite subnumber",
  "Duration",
  "Action pointer",
  "Next frame",
  "Unknown 1",
  "Unknown 2",
  NULL
};

static const char * const dehack_ammos [] =
{
  "Max ammo",
  "Per ammo",
  NULL
};


static const char * const dehack_weapons [] =
{
  "Ammo type",
  "Deselect frame",
  "Select frame",
  "Bobbing frame",
  "Shooting frame",
  "Firing frame",
  NULL
};

static const char * const dehack_pointers [] =
{
  "Codep Frame",
  NULL
};

static const char * const dehack_cheats [] =
{
  "Change music",
  "Chainsaw",
  "God mode",
  "Ammo & Keys",
  "Ammo",
  "No Clipping 1",
  "No Clipping 2",
  "Invincibility",
  "Berserk",
  "Invisibility",
  "Radiation Suit",
  "Auto-map",
  "Lite-Amp Goggles",
  "BEHOLD menu",
  "Level Warp",
  "Player Position",
  "Map cheat",
  NULL
};

static const char * const dehack_miscs [] =
{
  "Initial Health",
  "Initial Bullets",
  "Max Health",
  "Max Armor",
  "Max Armour",
  "Green Armor Class",
  "Green Armour Class",
  "Blue Armor Class",
  "Blue Armour Class",
  "Max Soulsphere",
  "Soulsphere Health",
  "Megasphere Health",
  "God Mode Health",
  "IDFA Armor",
  "IDFA Armour",
  "IDFA Armor Class",
  "IDFA Armour Class",
  "IDKFA Armor",
  "IDKFA Armour",
  "IDKFA Armor Class",
  "IDKFA Armour Class",
  "BFG Cells/Shot",
  "Monsters Infight",
  "Player Jump",
  "Homing Missiles",
  NULL
};

static const char * const dehack_codeptrs [] =
{
  "FRAME",
  NULL
};

static const char * const dehack_codeptr_frames [] =
{
  "NULL",
  "Light0", "WeaponReady", "Lower", "Raise",
  "Punch", "ReFire", "FirePistol", "Light1",
  "FireShotgun", "Light2", "FireShotgun2", "CheckReload",
  "OpenShotgun2", "LoadShotgun2", "CloseShotgun2", "FireCGun",
  "GunFlash", "FireMissile", "Saw", "FirePlasma",
  "BFGsound", "FireBFG", "BFGSpray", "Explode", "Pain",
  "PlayerScream", "Fall", "XScream", "Look", "Chase",
  "FaceTarget", "PosAttack", "Scream", "SPosAttack", "VileChase",
  "VileStart", "VileTarget", "VileAttack", "StartFire", "Fire",
  "FireCrackle", "Tracer", "SkelWhoosh", "SkelFist", "SkelMissile",
  "FatRaise", "FatAttack1", "FatAttack2", "FatAttack3",
  "BossDeath", "CPosAttack", "CPosRefire", "TroopAttack",
  "SargAttack", "HeadAttack", "BruisAttack", "SkullAttack",
  "Metal", "SpidRefire", "BabyMetal", "BspiAttack",
  "Hoof", "CyberAttack", "PainAttack", "PainDie", "KeenDie",
  "BrainPain", "BrainScream", "BrainDie", "BrainAwake",
  "BrainSpit", "SpawnSound", "SpawnFly", "BrainExplode",
  NULL
};

/* In same order as above!!! */

static const actionf_t action_ptrs[] =
{
  {NULL},
  {A_Light0}, {A_WeaponReady}, {A_Lower}, {A_Raise},
  {A_Punch}, {A_ReFire}, {A_FirePistol}, {A_Light1},
  {A_FireShotgun}, {A_Light2}, {A_FireShotgun2}, {A_CheckReload},
  {A_OpenShotgun2}, {A_LoadShotgun2}, {A_CloseShotgun2}, {A_FireCGun},
  {A_GunFlash}, {A_FireMissile}, {A_Saw}, {A_FirePlasma},
  {A_BFGsound}, {A_FireBFG}, {A_BFGSpray}, {A_Explode}, {A_Pain},
  {A_PlayerScream}, {A_Fall}, {A_XScream}, {A_Look}, {A_Chase},
  {A_FaceTarget}, {A_PosAttack}, {A_Scream}, {A_SPosAttack}, {A_VileChase},
  {A_VileStart}, {A_VileTarget}, {A_VileAttack}, {A_StartFire}, {A_Fire},
  {A_FireCrackle}, {A_Tracer}, {A_SkelWhoosh}, {A_SkelFist}, {A_SkelMissile},
  {A_FatRaise}, {A_FatAttack1}, {A_FatAttack2}, {A_FatAttack3},
  {A_BossDeath}, {A_CPosAttack}, {A_CPosRefire}, {A_TroopAttack},
  {A_SargAttack}, {A_HeadAttack}, {A_BruisAttack}, {A_SkullAttack},
  {A_Metal}, {A_SpidRefire}, {A_BabyMetal}, {A_BspiAttack},
  {A_Hoof}, {A_CyberAttack}, {A_PainAttack}, {A_PainDie}, {A_KeenDie},
  {A_BrainPain}, {A_BrainScream}, {A_BrainDie}, {A_BrainAwake},
  {A_BrainSpit}, {A_SpawnSound}, {A_SpawnFly}, {A_BrainExplode}
};

/* We cannot replace a A_* function that takes a mobj pointer */
/* with one that takes a player_t pointer as *bad* things happen. */
/* Harmony.wad wants to use A_CloseShotgun2 in place of A_BFGSpray */
/* which crashes doom. */

static const unsigned char action_player_type[] =
{
  255,
  1, 1, 1, 1,	// {A_Light0}, {A_WeaponReady}, {A_Lower}, {A_Raise},
  1, 1, 1, 1,	// {A_Punch}, {A_ReFire}, {A_FirePistol}, {A_Light1},
  1, 1, 1, 1,	// {A_FireShotgun}, {A_Light2}, {A_FireShotgun2}, {A_CheckReload},
  1, 1, 1, 1,	// {A_OpenShotgun2}, {A_LoadShotgun2}, {A_CloseShotgun2}, {A_FireCGun},
  1, 1, 1, 1,	// {A_GunFlash}, {A_FireMissile}, {A_Saw}, {A_FirePlasma},
  1, 1, 0, 0, 0,// {A_BFGsound}, {A_FireBFG}, {A_BFGSpray}, {A_Explode}, {A_Pain},
  0, 0, 0, 0, 0,// {A_PlayerScream}, {A_Fall}, {A_XScream}, {A_Look}, {A_Chase},
  0, 0, 0, 0, 0,// {A_FaceTarget}, {A_PosAttack}, {A_Scream}, {A_SPosAttack}, {A_VileChase},
  0, 0, 0, 0, 0,// {A_VileStart}, {A_VileTarget}, {A_VileAttack}, {A_StartFire}, {A_Fire},
  0, 0, 0, 0, 0,// {A_FireCrackle}, {A_Tracer}, {A_SkelWhoosh}, {A_SkelFist}, {A_SkelMissile},
  0, 0, 0, 0,	// {A_FatRaise}, {A_FatAttack1}, {A_FatAttack2}, {A_FatAttack3},
  0, 0, 0, 0,	// {A_BossDeath}, {A_CPosAttack}, {A_CPosRefire}, {A_TroopAttack},
  0, 0, 0, 0,	// {A_SargAttack}, {A_HeadAttack}, {A_BruisAttack}, {A_SkullAttack},
  0, 0, 0, 0,	// {A_Metal}, {A_SpidRefire}, {A_BabyMetal}, {A_BspiAttack},
  0, 0, 0, 0, 0,// {A_Hoof}, {A_CyberAttack}, {A_PainAttack}, {A_PainDie}, {A_KeenDie},
  0, 0, 0, 0,	// {A_BrainPain}, {A_BrainScream}, {A_BrainDie}, {A_BrainAwake},
  0, 0, 0, 0	// {A_BrainSpit}, {A_SpawnSound}, {A_SpawnFly}, {A_BrainExplode}
};

/* These tables are in the same order as the declarations of the messages */

static const char * const dehack_monster_obit_strings [] =
{
  "OB_ZOMBIE",
  "OB_SHOTGUY",
  "OB_CHAINGUY",
  "OB_WOLFSS",
  "OB_IMP",
  "OB_DEMON",
  "OB_SPECTRE",
  "OB_SKULL",
  "OB_CACO",
  "OB_KNIGHT",
  "OB_BARON",
  "OB_BABY",
  "OB_PAIN",
  "OB_UNDEAD",
  "OB_FATSO",
  "OB_VILE",
  "OB_SPIDER",
  "OB_CYBORG",
  NULL
};

static const char * const dehack_other_obit_strings [] =
{
  "OB_BARREL",
  "OB_CRUSH",
  "OB_LAVA",
  "OB_KILLEDSELF",
#if 0
  "OB_UNDEADHIT",
  "OB_IMPHIT",
  "OB_CACOHIT",
  "OB_DEMONHIT",
  "OB_SPECTREHIT",
  "OB_BARONHIT",
  "OB_KNIGHTHIT",

  "OB_SUICIDE",
  "OB_FALLING",
  "OB_EXIT",
  "OB_WATER",
  "OB_SLIME",
  "OB_SPLASH",
  "OB_R_SPLASH",
  "OB_ROCKET",
  "OB_KILLEDSELF",

  "OB_STEALTHBABY",
  "OB_STEALTHVILE",
  "OB_STEALTHBARON",
  "OB_STEALTHCACO",
  "OB_STEALTHCHAINGUY",
  "OB_STEALTHDEMON",
  "OB_STEALTHKNIGHT",
  "OB_STEALTHIMP",
  "OB_STEALTHFATSO",
  "OB_STEALTHUNDEAD",
  "OB_STEALTHSHOTGUY",
  "OB_STEALTHZOMBIE",


  "OB_MPFIST",
  "OB_MPCHAINSAW",
  "OB_MPPISTOL",
  "OB_MPSHOTGUN",
  "OB_MPSSHOTGUN",
  "OB_MPCHAINGUN",
  "OB_MPROCKET",
  "OB_MPR_SPLASH",
  "OB_MPPLASMARIFLE",
  "OB_MPBFG_BOOM",
  "OB_MPBFG_SPLASH",
  "OB_MPTELEFRAG",
  "OB_RAILGUN",
  "OB_MONTELEFRAG",
  "OB_DEFAULT",

  "OB_FRIENDLY1",
  "OB_FRIENDLY2",
  "OB_FRIENDLY3",
  "OB_FRIENDLY4",
#endif
  NULL
};

static const char * const dehack_cast_strings [] =
{
  "CC_ZOMBIE",
  "CC_SHOTGUN",
  "CC_HEAVY",
  "CC_WOLFSS",
  "CC_IMP",
  "CC_DEMON",
  "CC_SPECTRE",
  "CC_LOST",
  "CC_CACO",
  "CC_HELL",
  "CC_BARON",
  "CC_ARACH",
  "CC_PAIN",
  "CC_REVEN",
  "CC_MANCU",
  "CC_ARCH",
  "CC_SPIDER",
  "CC_CYBER",
  "CC_HERO",
  NULL
};

static const char * const dehack_require_key_strings [] =
{
  "PD_BLUEO",
  "PD_REDO",
  "PD_YELLOWO",
  "PD_BLUEK",
  "PD_REDK",
  "PD_YELLOWK",
  "PD_BLUEC",
  "PD_REDC",
  "PD_YELLOWC",
  "PD_BLUES",
  "PD_REDS",
  "PD_YELLOWS",
  "PD_BLUECO",
  "PD_REDCO",
  "PD_YELLOWCO",
  "PD_BLUESO",
  "PD_REDSO",
  "PD_YELLOWSO",
  "PD_ANY",
  "PD_ANYOBJ",
  "PD_ALL3",
  "PD_ALL3O",
  "PD_ALL6",
  "PD_ALL6O",
  "PD_ALLKEYS",
  NULL
};

static const char * const dehack_got_strings [] =
{
  "GOTARMOR",
  "GOTMEGA",
  "GOTHTHBONUS",
  "GOTARMBONUS",
  "GOTSTIM",
  "GOTMEDINEED",
  "GOTMEDIKIT",
  "GOTSUPER",
  "GOTBLUECARD",
  "GOTYELWCARD",
  "GOTREDCARD",
  "GOTBLUESKUL",
  "GOTYELWSKUL",
  "GOTREDSKUL",
  "GOTINVUL",
  "GOTBERSERK",
  "GOTINVIS",
  "GOTSUIT",
  "GOTMAP",
  "GOTVISOR",
  "GOTMSPHERE",
  "GOTCLIP",
  "GOTCLIPBOX",
  "GOTROCKET",
  "GOTROCKBOX",
  "GOTCELL",
  "GOTCELLBOX",
  "GOTSHELLS",
  "GOTSHELLBOX",
  "GOTBACKPACK",
  "GOTBFG9000",
  "GOTCHAINGUN",
  "GOTCHAINSAW",
  "GOTLAUNCHER",
  "GOTPLASMA",
  "GOTSHOTGUN",
  "GOTSHOTGUN2",
  NULL
};

static const char * const dehack_playernames [] =
{
  "HUSTR_PLRGREEN",
  "HUSTR_PLRINDIGO",
  "HUSTR_PLRBROWN",
  "HUSTR_PLRRED",
  NULL
};

static const char * const stat_bar_message_names [] =
{
  "STSTR_MUS",
  "STSTR_NOMUS",
  "STSTR_DQDON",
  "STSTR_DQDOFF",
  "STSTR_KFAADDED",
  "STSTR_FAADDED",
  "STSTR_NCON",
  "STSTR_NCOFF",
  "STSTR_BEHOLD",
  "STSTR_BEHOLDX",
  "STSTR_CHOPPERS",
  "STSTR_CLEV",
  NULL
};

static const char * const am_map_message_names [] =
{
  "AMSTR_FOLLOWON",
  "AMSTR_FOLLOWOFF",
  "AMSTR_GRIDON",
  "AMSTR_GRIDOFF",
  "AMSTR_MARKEDSPOT",
  "AMSTR_MARKSCLEARED",
  NULL
};

static const char * const menu_message_names [] =
{
  "LOADNET",
  "QLOADNET",
  "QSAVESPOT",
  "SAVEDEAD",
  "QSPROMPT",
  "QLPROMPT",
  "NEWGAME",
  "NIGHTMARE",
  "SWSTRING",
  "MSGOFF",
  "MSGON",
  "NETEND",
  "ENDGAME",
  "DOSY",
  "DETAILHI",
  "DETAILLO",
  "GAMMALVL0",
  "GAMMALVL1",
  "GAMMALVL2",
  "GAMMALVL3",
  "GAMMALVL4",
  "EMPTYSTRING",
  NULL
};

typedef struct
{
  char * name;
  unsigned int value;
} bit_names_t;

static const bit_names_t dehack_thing_bit_names [] =
{
  { "SPECIAL",		MF_SPECIAL},
  { "SOLID",		MF_SOLID},
  { "SHOOTABLE",	MF_SHOOTABLE},
  { "NOSECTOR",		MF_NOSECTOR},
  { "NOBLOCKMAP",	MF_NOBLOCKMAP},
  { "AMBUSH",		MF_AMBUSH},
  { "JUSTHIT",		MF_JUSTHIT},
  { "JUSTATTACKED",	MF_JUSTATTACKED},
  { "SPAWNCEILING",	MF_SPAWNCEILING},
  { "NOGRAVITY",	MF_NOGRAVITY},
  { "DROPOFF",		MF_DROPOFF},
  { "PICKUP",		MF_PICKUP},
  { "NOCLIP",		MF_NOCLIP},
  { "SLIDE",		MF_SLIDE},
  { "FLOAT",		MF_FLOAT},
  { "TELEPORT",		MF_TELEPORT},
  { "MISSILE",		MF_MISSILE},
  { "DROPPED",		MF_DROPPED},
  { "SHADOW",		MF_SHADOW},
  { "NOBLOOD",		MF_NOBLOOD},
  { "CORPSE",		MF_CORPSE},
  { "INFLOAT",		MF_INFLOAT},
  { "COUNTKILL",	MF_COUNTKILL},
  { "COUNTITEM",	MF_COUNTITEM},
  { "SKULLFLY",		MF_SKULLFLY},
  { "NOTDMATCH",	MF_NOTDMATCH},
  { "TRANSLATION",	MF_TRANSLATION},
  { "BOUNCES",		MF_BOUNCES}
};

/* ---------------------------------------------------------------------------- */

/* Need a private copy of this table (from info.c) to prevent */
/* problems with circular modifications */



static const actionf_t states_ptr_copy[NUMSTATES] =
{
  {NULL}, {A_Light0}, {A_WeaponReady}, {A_Lower}, {A_Raise}, {NULL},
  {A_Punch}, {NULL}, {NULL}, {A_ReFire}, {A_WeaponReady}, {A_Lower},
  {A_Raise}, {NULL}, {A_FirePistol}, {NULL}, {A_ReFire}, {A_Light1},
  {A_WeaponReady}, {A_Lower}, {A_Raise}, {NULL}, {A_FireShotgun}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_ReFire}, {A_Light1}, {A_Light2},
  {A_WeaponReady}, {A_Lower}, {A_Raise}, {NULL}, {A_FireShotgun2}, {NULL},
  {A_CheckReload}, {A_OpenShotgun2}, {NULL}, {A_LoadShotgun2}, {NULL},
  {A_CloseShotgun2}, {A_ReFire}, {NULL}, {NULL}, {A_Light1}, {A_Light2},
  {A_WeaponReady}, {A_Lower}, {A_Raise}, {A_FireCGun}, {A_FireCGun}, {A_ReFire},
  {A_Light1}, {A_Light2}, {A_WeaponReady}, {A_Lower}, {A_Raise}, {A_GunFlash},
  {A_FireMissile}, {A_ReFire}, {A_Light1}, {NULL}, {A_Light2}, {A_Light2},
  {A_WeaponReady}, {A_WeaponReady}, {A_Lower}, {A_Raise}, {A_Saw}, {A_Saw},
  {A_ReFire}, {A_WeaponReady}, {A_Lower}, {A_Raise}, {A_FirePlasma}, {A_ReFire},
  {A_Light1}, {A_Light1}, {A_WeaponReady}, {A_Lower}, {A_Raise}, {A_BFGsound},
  {A_GunFlash}, {A_FireBFG}, {A_ReFire}, {A_Light1}, {A_Light2}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_BFGSpray}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Explode}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Pain}, {NULL},
  {A_PlayerScream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_XScream},
  {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Look}, {A_Look},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_FaceTarget}, {A_PosAttack}, {NULL}, {NULL}, {A_Pain}, {NULL},
  {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {A_XScream}, {A_Fall}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_SPosAttack}, {NULL},
  {NULL}, {A_Pain}, {NULL}, {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL},
  {A_XScream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {A_Look}, {A_Look}, {A_VileChase}, {A_VileChase},
  {A_VileChase}, {A_VileChase}, {A_VileChase}, {A_VileChase}, {A_VileChase},
  {A_VileChase}, {A_VileChase}, {A_VileChase}, {A_VileChase}, {A_VileChase},
  {A_VileStart}, {A_FaceTarget}, {A_VileTarget}, {A_FaceTarget}, {A_FaceTarget},
  {A_FaceTarget}, {A_FaceTarget}, {A_FaceTarget}, {A_FaceTarget}, {A_VileAttack},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {A_Fall},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_StartFire},
  {A_Fire}, {A_Fire}, {A_Fire}, {A_FireCrackle}, {A_Fire}, {A_Fire}, {A_Fire},
  {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire},
  {A_Fire}, {A_Fire}, {A_FireCrackle}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire},
  {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {A_Tracer}, {A_Tracer}, {NULL}, {NULL}, {NULL},
  {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_FaceTarget}, {A_SkelWhoosh}, {A_FaceTarget}, {A_SkelFist}, {A_FaceTarget},
  {A_FaceTarget}, {A_SkelMissile}, {A_FaceTarget}, {NULL}, {A_Pain}, {NULL},
  {NULL}, {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Look}, {A_Look},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_FatRaise},
  {A_FatAttack1}, {A_FaceTarget}, {A_FaceTarget}, {A_FatAttack2}, {A_FaceTarget},
  {A_FaceTarget}, {A_FatAttack3}, {A_FaceTarget}, {A_FaceTarget}, {NULL},
  {A_Pain}, {NULL}, {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {A_BossDeath}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_CPosAttack},
  {A_CPosAttack}, {A_CPosRefire}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {A_Fall},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_XScream}, {A_Fall}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Look},
  {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget}, {A_TroopAttack}, {NULL},
  {A_Pain}, {NULL}, {A_Scream}, {NULL}, {A_Fall}, {NULL}, {NULL}, {A_XScream},
  {NULL}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget},
  {A_SargAttack}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {NULL}, {A_Fall},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Look},
  {A_Chase}, {A_FaceTarget}, {A_FaceTarget}, {A_HeadAttack}, {NULL}, {A_Pain},
  {NULL}, {NULL}, {A_Scream}, {NULL}, {NULL}, {A_Fall}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget},
  {A_BruisAttack}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {NULL}, {A_Fall},
  {NULL}, {NULL}, {A_BossDeath}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget},
  {A_BruisAttack}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {NULL}, {A_Fall},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {A_Look}, {A_Look}, {A_Chase}, {A_Chase}, {A_FaceTarget},
  {A_SkullAttack}, {NULL}, {NULL}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {NULL},
  {A_Fall}, {NULL}, {NULL}, {A_Look}, {A_Look}, {A_Metal}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Metal}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Metal}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_SPosAttack}, {A_SPosAttack},
  {A_SpidRefire}, {NULL}, {A_Pain}, {A_Scream}, {A_Fall}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_BossDeath}, {A_Look},
  {A_Look}, {NULL}, {A_BabyMetal}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_BabyMetal}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_FaceTarget}, {A_BspiAttack}, {NULL}, {A_SpidRefire}, {NULL}, {A_Pain},
  {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {NULL}, {A_BossDeath}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {A_Look}, {A_Look}, {A_Hoof}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Metal}, {A_Chase},
  {A_FaceTarget}, {A_CyberAttack}, {A_FaceTarget}, {A_CyberAttack}, {A_FaceTarget},
  {A_CyberAttack}, {A_Pain}, {NULL}, {A_Scream}, {NULL}, {NULL}, {NULL}, {A_Fall},
  {NULL}, {NULL}, {NULL}, {A_BossDeath}, {A_Look}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget}, {A_FaceTarget},
  {A_PainAttack}, {NULL}, {A_Pain}, {NULL}, {A_Scream}, {NULL}, {NULL},
  {A_PainDie}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {A_Look},
  {A_Look}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase}, {A_Chase},
  {A_Chase}, {A_Chase}, {A_FaceTarget}, {A_FaceTarget}, {A_CPosAttack},
  {A_FaceTarget}, {A_CPosAttack}, {A_CPosRefire}, {NULL}, {A_Pain}, {NULL},
  {A_Scream}, {A_Fall}, {NULL}, {NULL}, {NULL}, {A_XScream}, {A_Fall}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {A_Scream}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {A_KeenDie}, {NULL}, {NULL}, {A_Pain}, {NULL}, {A_BrainPain},
  {A_BrainScream}, {NULL}, {NULL}, {A_BrainDie}, {A_Look}, {A_BrainAwake},
  {A_BrainSpit}, {A_SpawnSound}, {A_SpawnFly}, {A_SpawnFly}, {A_SpawnFly},
  {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire}, {A_Fire},
  {NULL}, {NULL}, {A_BrainExplode}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {A_Scream}, {NULL}, {A_Explode}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL}, {NULL},
  {NULL}, {NULL}
};

/* ---------------------------------------------------------------------------- */

#ifdef CREATE_DEHACK_FILE
static const char * const thing_names [] =
{
  "Player","Trooper","Sargeant","Archvile","Archvile Attack","Revenant",
  "Revenant Fireball","Fireball Trail","Mancubus","Mancubus Fireball",
  "Chaingun Sargeant","Imp","Demon","Spectre","Cacodemon","Baron of Hell",
  "Baron Fireball","Hell Knight","Lost Soul","Spiderdemon","Arachnotron",
  "Cyberdemon","Pain Elemental","SS Nazi","Commander Keen","Big Brain",
  "Demon Spawner","Demon Spawn Spot","Demon Spawn Cube","Demon Spawn Fire",
  "Barrel","Imp Fireball","Caco Fireball","Rocket (in air)","Plasma Bullet",
  "BFG Shot","Arach. Fireball","Bullet Puff","Blood Splat","Teleport Flash",
  "Item Respawn Fog","Teleport Exit","BFG Hit","Green Armor","Blue Armor",
  "Health Potion","Armor Helmet","Blue Keycard","Red Keycard","Yellow Keycard",
  "Yellow Skull Key","Red Skull Key","Blue Skull Key","Stim Pack","Medical Kit",
  "Soul Sphere","Invulnerability","Berserk Sphere","Blur Sphere","Radiation Suit",
  "Computer Map","Lite Amp. Visor","Mega Sphere","Ammo Clip","Box of Ammo",
  "Rocket","Box of Rockets","Energy Cell","Energy Pack","Shells","Box of Shells",
  "Backpack","BFG 9000","Chaingun","Chainsaw","Rocket Launcher","Plasma Gun",
  "Shotgun","Super Shotgun","Tall Lamp","Tall Lamp 2","Short Lamp",
  "Tall Gr. Pillar","Short Gr. Pillar","Tall Red Pillar","Short Red Pillar",
  "Pillar w/Skull","Pillar w/Heart","Eye in Symbol","Flaming Skulls","Grey Tree",
  "Tall Blue Torch","Tall Green Torch","Tall Red Torch","Small Blue Torch",
  "Small Gr. Torch","Small Red Torch","Brown Stub","Technical Column","Candle",
  "Candelabra","Swaying Body","Hanging Arms Out","One-legged Body","Hanging Torso",
  "Hanging Leg","Hanging Arms Out2","Hanging Torso 2","One-legged Body 2","Hanging Leg 2",
  "Swaying Body 2","Dead Cacodemon","Dead Marine","Dead Trooper","Dead Demon",
  "Dead Lost Soul","Dead Imp","Dead Sargeant","Guts and Bones","Guts and Bones 2",
  "Skewered Heads","Pool of Blood","Pole with Skull","Pile of Skulls","Impaled Body",
  "Twitching Body","Large Tree","Flaming Barrel","Hanging Body 1","Hanging Body 2",
  "Hanging Body 3","Hanging Body 4","Hanging Body 5","Hanging Body 6","Pool Of Blood 1",
  "Pool Of Blood 2","Brains"
};

static const char * const ammo_names [] =
{
  "Bullets","Shells","Cells","Rockets"
};

static const char * const weapon_names [] =
{
  "Fists","Pistol","Shotgun","Chaingun","Rocket Launcher",
  "Plasma Gun","BFG 9000","Chainsaw","Super Shotgun"
};

#endif
/* ---------------------------------------------------------------------------- */
// Americans cannot spell...

typedef struct
{
  const char * wrong;
  const char * correct;
} spellings_t;

static const spellings_t spelling_corrections [] =
{
  { "armor", "armour" },
  { "center", "centre" },
  { "rappel", "abseil" },
  { "neighbor", "neighbour" },
  { "refueling", "refuelling" },
  { "favor", "favour" },
  { "labor", "labour" },
  { "color", "colour" },
  { "traveling", "travelling" },
  { "traveled", "travelled" },
  { "fense", "fence" },			// defence, offence
  { "license", "licence" }
};

/* ---------------------------------------------------------------------------- */
#ifndef dh_strcmp
int dh_strcmp (char * s1, char * s2)
{
  // printf ("COMPARING\n%s\nWITH\n%s\n", s1, s2);
  return (strncasecmp (s1, s2, strlen(s2)));
}
#endif
/* ---------------------------------------------------------------------------- */
/*
   Works out whether the file pointer has reached (or nearly reached) the
   end of the file (or file within a wad file).
*/

int dh_feof (FILE * fin, unsigned int top)
{
  unsigned int current;

  if (top == ~0)			// Normal file?
    return (feof (fin));

  current = (unsigned int) ftell (fin);
  if ((current >= top)
  /* Still below - but if less than 5 bytes then treat as near enough! */
   || ((top-current) < 5))
    return (1);

  return (0);
}

/* ---------------------------------------------------------------------------- */

/* Similar to the standard fgets function, but strips out control characters  */
/* Mainly to convert from DOS format files, which appears to be the format    */
/* of many DeHackEd files. */

void dh_fgets (char * a_line, unsigned int max_length, FILE * fin)
{
  int p;

  do
  {
    p = fgetc (fin);
    if (max_length) max_length--;
    while ((p >= 0) && (p <= 31) && (p != 10))
    {
      p = fgetc (fin);
      if (max_length) max_length--;
    }

    if ((p == EOF) || (p == 10)) p = 0;
    *a_line++ = p;

    if (max_length == 0)
    {
      p = *a_line = 0;
    }
  } while (p);
}

/* ---------------------------------------------------------------------------- */

static void dh_fgets_x (char * a_line, unsigned int max_length, FILE * fin, unsigned int filetop_pos)
{
  unsigned int max_chars;

  if (filetop_pos != ~0)
  {
    max_chars = (unsigned int) ftell (fin);
    if (max_chars >= filetop_pos)
    {
      a_line [0] = 0;
      return;
    }

    max_chars = filetop_pos - max_chars;
    if (max_chars < max_length)
      max_length = max_chars;
  }

  dh_fgets (a_line, max_length, fin);
}

/* ---------------------------------------------------------------------------- */

static char * next_arg (char * ptr)
{
  while (*ptr > ' ')
    ptr++;

  while (*ptr == ' ')
    ptr++;

  return (ptr);
}

/* ---------------------------------------------------------------------------- */

/* Search for 'search_string'  within 'text' */
/* Returns 0 if not found else returns       */
/* position of text within string.           */

unsigned int dh_instr (const char * text, const char * search_string)
{
  unsigned int c1,c2;
  unsigned int pos1;
  unsigned int pos2;

  if (text[0] != 0)
  {
    pos1 = 0;
    do
    {
      pos2 = 0;
      do
      {
	c1 = toupper(search_string[pos2]);
	if (c1 == 0)
	  return (pos1 + 1);
	c2 = toupper (text[pos1+pos2]);
	pos2++;
      } while (c1 == c2);
      pos1++;
    } while (text[pos1] != 0);
  }

  return (0);
}

/* ---------------------------------------------------------------------------- */

/* Search for 'search_string'  within 'text' */
/* Returns 0 if not found else returns       */
/* position of text within string.           */

unsigned int dh_inchar (const char * text, char search_char)
{
  char cc;
  unsigned int i;

  cc = *text++;
  if (cc)
  {
    i = 0;
    search_char = toupper (search_char);
    do
    {
      i++;
      if (toupper (cc) == search_char)
	return (i);
      cc = *text++;
    } while (cc);
  }

  return (0);
}

/* ---------------------------------------------------------------------------- */

/* Attempts to open a file that is in the same directory as the executable */

static FILE * open_sibling_file (const char * filename, char * mode)
{
  char buffer[256];
  int i,j;

  i = -1;
  j = 0;

  do
  {
    buffer [j] = myargv [0][j];
    if (buffer [j] == DIRSEPC)
      i = j;
  } while (buffer [j++]);

  if (i == -1)
  {
    strcpy (buffer, filename);
  }
  else
  {
    buffer [i + 1] = 0;
    strcat (buffer, filename);
  }

  return (fopen (buffer, mode));
}

/* ---------------------------------------------------------------------------- */

/* Remove known American spellings from a text message and replace */
/* them with British versions. */

static void dh_correct_spelling (char * s1, const char * american, const char * british)
{
  unsigned int p;
  unsigned int q;
  unsigned int r;
  char or_mask;
  char and_mask;
  char cc;
  char temp_string [2048];

  p = dh_instr (s1, american);
  if (p)
  {
    p--;
    strncpy (temp_string, s1, p);

    /* Copy the new string across preserving the case. Don't think there's */
    /* really much point because Doom only uses upper case fonts. */

    or_mask  = 0x00;
    and_mask = 0xFF;
    q = r = p;
    while (*british)
    {
      cc = s1[r];
      if (cc)
      {
	r++;
      }
      else
      {
	cc = s1[r-1];
      }
      if ((cc >= 'A') && (cc <= 'Z'))
      {
	or_mask = 0x00;
	and_mask = 0xDF;
      }
      if ((cc >= 'a') && (cc <= 'z'))
      {
	or_mask = 0x20;
	and_mask = 0xFF;
      }
      cc = (*british++);
      if (((cc >= 'A') && (cc <= 'Z'))
       || ((cc >= 'a') && (cc <= 'z')))
      {
	cc = (cc | or_mask) & and_mask;
      }

      temp_string [q++] = cc;

    }
    temp_string [q] = 0;

    strcat  (temp_string, s1 + p + strlen(american));
    // printf ("CHANGED\n%s\n TO\n%s\n", s1, temp_string);
    strcpy  (s1, temp_string);
  }
}

/* ---------------------------------------------------------------------------- */

static void dh_remove_americanisms (char * s1)
{
  unsigned int i;
  unsigned int j;
  const spellings_t * spell;
  FILE * spells;
  char word1 [32];
  char word2 [32];
  char a_line [256];


  j = ARRAY_SIZE (spelling_corrections);
  spell = spelling_corrections;
  do
  {
    dh_correct_spelling (s1, spell -> wrong, spell -> correct);
    spell++;
  } while (--j);

  spells = open_sibling_file ("britspell", "r");
  if (spells)
  {
    do
    {
      dh_fgets (a_line, 250, spells);
      i = 0;
      j = 0;

      while ((isalpha (a_line [i])) && (j < 32))
      {
	word1 [j] = a_line [i];
	i++;
	j++;
      }
      word1 [j] = 0;

      if (j)
      {
	while (!(isalpha (a_line [i])))
	{
	  i++;
	}

	j = 0;
	while ((isalpha (a_line [i])) && (j < 32))
	{
	  word2 [j] = a_line [i];
	  i++;
	  j++;
	}
	word2 [j] = 0;

	if (j)
	{
	  // printf ("Looking to change %s into %s\n", word1, word2);
	  dh_correct_spelling (s1, word1, word2);
	}
      }
    } while (!feof(spells));
    fclose (spells);
  }
}

/* ---------------------------------------------------------------------------- */

#ifdef CREATE_DEHACK_FILE
static void write_all_things (FILE * fout)
{
  int thing_no;
  mobjinfo_t * ptr;

  ptr = &mobjinfo[0];


  thing_no = 0;
  do
  {
    fprintf (fout, "%s %d (%s)\n", dehack_patches[1], thing_no+1, thing_names[thing_no]);

    fprintf (fout, "%s = %d\n", dehack_things [0], ptr -> doomednum);
    fprintf (fout, "%s = %d\n", dehack_things [1], ptr -> spawnstate);
    fprintf (fout, "%s = %d\n", dehack_things [2], ptr -> spawnhealth);
    fprintf (fout, "%s = %d\n", dehack_things [3], ptr -> seestate);
    fprintf (fout, "%s = %d\n", dehack_things [4], ptr -> seesound);
    fprintf (fout, "%s = %d\n", dehack_things [5], ptr -> reactiontime);
    fprintf (fout, "%s = %d\n", dehack_things [6], ptr -> attacksound);
    fprintf (fout, "%s = %d\n", dehack_things [7], ptr -> painstate);
    fprintf (fout, "%s = %d\n", dehack_things [8], ptr -> painchance);
    fprintf (fout, "%s = %d\n", dehack_things [9], ptr -> painsound);
    fprintf (fout, "%s = %d\n", dehack_things [10], ptr -> meleestate);
    fprintf (fout, "%s = %d\n", dehack_things [11], ptr -> missilestate);
    fprintf (fout, "%s = %d\n", dehack_things [12], ptr -> deathstate);
    fprintf (fout, "%s = %d\n", dehack_things [13], ptr -> xdeathstate);
    fprintf (fout, "%s = %d\n", dehack_things [14], ptr -> deathsound);
    fprintf (fout, "%s = %d\n", dehack_things [15], ptr -> speed);
    fprintf (fout, "%s = %d\n", dehack_things [16], ptr -> radius);
    fprintf (fout, "%s = %d\n", dehack_things [17], ptr -> height);
    fprintf (fout, "%s = %d\n", dehack_things [18], ptr -> mass);
    fprintf (fout, "%s = %d\n", dehack_things [19], ptr -> damage);
    fprintf (fout, "%s = %d\n", dehack_things [20], ptr -> activesound);
    fprintf (fout, "%s = %d\n", dehack_things [21], ptr -> flags);
    fprintf (fout, "%s = %d\n", dehack_things [22], ptr -> raisestate);
    fprintf (fout, "%s = %d\n", dehack_things [23], ptr -> scale);

    fprintf (fout, "\n\n");
    ptr++;
    thing_no++;
  } while (thing_no < NUMMOBJTYPES);

}
#endif

/* ---------------------------------------------------------------------------- */

static int find_thing_bitname (char * str)
{
  char cc;
  unsigned int len;
  unsigned int count;
  const bit_names_t * ptr;
  char buf [40];

  len = 0;
  do
  {
    cc = str [len];
    if (cc <= ' ')
      cc = 0;
    buf [len++] = cc;
  } while (cc);

  ptr = dehack_thing_bit_names;
  count = ARRAY_SIZE (dehack_thing_bit_names);
  do
  {
    if (strcasecmp (ptr->name, buf) == 0)
      return (ptr -> value);
    ptr++;
  } while (--count);

  return (0);
}

/* ---------------------------------------------------------------------------- */

static void decode_things_bits (unsigned int * params, char * string1)
{
  unsigned int flag;
  char operator;

  params [0] = 0;
  operator = '|';

  do
  {
    flag = find_thing_bitname (string1);
    switch (operator)
    {
      case '|': params [0] |= flag; break;
      case '+': params [0] += flag; break;
      case '&': params [0] &= flag; break;
    }
    string1 = next_arg (string1);
    if (*string1 == 0)
      break;
    operator = *string1;
    string1 = next_arg (string1);
  } while (*string1);
}

/* ---------------------------------------------------------------------------- */

static void dh_write_to_thing (unsigned int number, unsigned int record, unsigned int value)
{
  mobjinfo_t * ptr;

  ptr = &mobjinfo[number-1];

  switch (record)
  {
    case  0:ptr -> doomednum	= value; break;
    case  1:ptr -> spawnstate	= value; break;
    case  2:ptr -> spawnhealth	= value; break;
    case  3:ptr -> seestate	= value; break;
    case  4:ptr -> seesound	= value; break;
    case  5:ptr -> reactiontime	= value; break;
    case  6:ptr -> attacksound	= value; break;
    case  7:ptr -> painstate	= value; break;
    case  8:ptr -> painchance	= value; break;
    case  9:ptr -> painsound	= value; break;
    case 10:ptr -> meleestate	= value; break;
    case 11:ptr -> missilestate	= value; break;
    case 12:ptr -> deathstate	= value; break;
    case 13:ptr -> xdeathstate	= value; break;
    case 14:ptr -> deathsound	= value; break;
    case 15:ptr -> speed	= value; break;
    case 16:ptr -> radius	= value;
	    ptr -> pickupradius	= value; break;
    case 17:ptr -> height	= value; break;
    case 18:ptr -> mass		= value; break;
    case 19:ptr -> damage	= value; break;
    case 20:ptr -> activesound	= value; break;
    case 21:ptr -> flags	= value; break;
    case 22:ptr -> raisestate	= value; break;
    case 23:ptr -> scale	= value; break;
    default:fprintf (stderr, "Invalid Thing record\n");
  }
  // printf ("Patched element %d of THINGS %d to %X\n", record, number, value);
}

/* ---------------------------------------------------------------------------- */
#ifdef CREATE_DEHACK_FILE
static void write_all_sounds (FILE * fout)
{
  unsigned int sound_no;
  sfxinfo_t * ptr;

  ptr = &S_sfx[0];

  sound_no = 0;
  do
  {
    fprintf (fout, "%s %d\n", dehack_patches[2], sound_no);
    fprintf (fout, "%s = %d\n", dehack_sounds [0], (int) ptr -> name);
    fprintf (fout, "%s = %d\n", dehack_sounds [1], (int) ptr -> singularity);
    fprintf (fout, "%s = %d\n", dehack_sounds [2], (int) ptr -> priority);
    fprintf (fout, "%s = %d\n", dehack_sounds [3], (int) ptr -> link);
    fprintf (fout, "%s = %d\n", dehack_sounds [4], (int) ptr -> usefulness);
    fprintf (fout, "%s = %d\n", dehack_sounds [5], (int) ptr -> lumpnum);
    fprintf (fout, "%s = %d\n", dehack_sounds [6], (int) ptr -> data);
    fprintf (fout, "%s = %d\n", dehack_sounds [7], (int) ptr -> pitch);
    fprintf (fout, "%s = %d\n", dehack_sounds [8], (int) ptr -> volume);

    fprintf (fout, "\n\n");
    ptr++;
    sound_no++;
  } while (sound_no < NUMSFX);

}
#endif
/* ---------------------------------------------------------------------------- */

static void dh_write_to_sound (unsigned int number, unsigned int record, unsigned int value)
{
  sfxinfo_t * ptr;

  ptr = &S_sfx[number];

  switch (record)
  {
    case 0: //	"Offset",
      // ptr -> name = value;   Don't change pointers willy nilly!
      break;

    case 1: //	"Zero/One",
      ptr -> singularity = value;
      break;

    case 2: //	"Value",
      ptr -> priority = value;
      break;

    case 3: //	"Zero 1",
      // ptr -> link = value;   Don't change pointers willy nilly!
      break;

    case 4: //	"Zero 2",
      ptr -> usefulness = value;
      break;

    case 5: //	"Zero 3",
      ptr -> lumpnum = value;
      break;

    case 6: //	"Zero 4",
      // ptr -> data = value;   Don't change pointers willy nilly!
      break;

    case 7: //	"Neg. One 1",
      ptr -> pitch = value;
      break;

    case 8: //	"Neg. One 2"
      ptr -> volume = value;
      break;
  }
}

/* ---------------------------------------------------------------------------- */

#ifdef CREATE_DEHACK_FILE
static void write_all_frames (FILE * fout)
{
  unsigned int frame_no;
  unsigned int counter;
  state_t * ptr;

  ptr = &states[0];

  frame_no = 0;

  do
  {
    fprintf (fout, "%s %d\n", dehack_patches[3], frame_no);
    fprintf (fout, "%s = %d\n", dehack_frames[0], (int) ptr -> sprite);
    fprintf (fout, "%s = %d\n", dehack_frames[1], (int) ptr -> frame);
    fprintf (fout, "%s = %d\n", dehack_frames[2], (int) ptr -> tics);

    counter = 0;
    while (action_ptrs[counter].acv != ptr -> action.acv)
    {
      counter++;
    }
    fprintf (fout, "%s = %d\n", dehack_frames[3], counter);

    fprintf (fout, "%s = %d\n", dehack_frames[4], (int) ptr -> nextstate);
    fprintf (fout, "%s = %d\n", dehack_frames[5], (int) ptr -> misc1);
    fprintf (fout, "%s = %d\n", dehack_frames[6], (int) ptr -> misc2);
    fprintf (fout, "\n\n");
    ptr++;
    frame_no++;
  } while (frame_no < NUMSTATES);
}
#endif

/* ---------------------------------------------------------------------------- */

static void dh_write_to_frame (unsigned int number, unsigned int record, unsigned int value)
{
  state_t * ptr;

  ptr = &states[number];

  switch (record)
  {
    case  0:ptr -> sprite	 = (spritenum_t) value; break;
    case  1:ptr -> frame	 = value; break;
    case  2:ptr -> tics		 = value; break;
    case  3:/* ptr -> action.acv  = (void*)value; */ break;
    case  4:ptr -> nextstate	 = (statenum_t) value; break;
    case  5:ptr -> misc1	 = value; break;
    case  6:ptr -> misc2	 = value; break;
    default:fprintf (stderr, "Invalid Frame record\n");
  }
  // printf ("Patched element %d of FRAMES %d to %d\n", record, number, value);
}

/* ---------------------------------------------------------------------------- */

static void dh_write_to_sprite (unsigned int number, unsigned int record, unsigned int value)
{
}

/* ---------------------------------------------------------------------------- */
#ifdef CREATE_DEHACK_FILE
static void write_all_ammos (FILE * fout)
{
  unsigned int ammo_no;

  ammo_no = 0;

  do
  {
    fprintf (fout, "%s %d (%s)\n", dehack_patches[5], ammo_no, ammo_names[ammo_no]);
    fprintf (fout, "%s = %d\n", dehack_ammos[0], maxammo[ammo_no]);
    fprintf (fout, "%s = %d\n", dehack_ammos[1], clipammo[ammo_no]);
    fprintf (fout, "\n\n");
    ammo_no++;
  } while (ammo_no < 4);
}
#endif
/* ---------------------------------------------------------------------------- */

static void dh_write_to_ammo (unsigned int number, unsigned int record, unsigned int value)
{
  switch (record)
  {
    case 0:  // "Max ammo"
      maxammo [number] = value;
      break;

    case 1:  // "Per ammo"
      clipammo [number] = value;
      break;
  }
}

/* ---------------------------------------------------------------------------- */
#ifdef CREATE_DEHACK_FILE
static void write_all_weapons (FILE * fout)
{
  unsigned int weapon_no;
  weaponinfo_t * ptr;

  ptr = &weaponinfo[0];

  weapon_no = 0;
  do
  {
    fprintf (fout, "%s %d (%s)\n", dehack_patches[6], weapon_no, weapon_names[weapon_no]);
    fprintf (fout, "%s = %d\n", dehack_weapons[0], (int) ptr -> ammo);
    fprintf (fout, "%s = %d\n", dehack_weapons[1], (int) ptr -> upstate);
    fprintf (fout, "%s = %d\n", dehack_weapons[2], (int) ptr -> downstate);
    fprintf (fout, "%s = %d\n", dehack_weapons[3], (int) ptr -> readystate);
    fprintf (fout, "%s = %d\n", dehack_weapons[4], (int) ptr -> atkstate);
    fprintf (fout, "%s = %d\n", dehack_weapons[5], (int) ptr -> flashstate);

    fprintf (fout, "\n\n");
    ptr++;
    weapon_no++;
  } while (weapon_no < NUMWEAPONS);

}
#endif
/* ---------------------------------------------------------------------------- */

static void dh_write_to_weapon (unsigned int number, unsigned int record, unsigned int value)
{
  weaponinfo_t * ptr;

  ptr = &weaponinfo[number];

  switch (record)
  {
    case 0:ptr -> ammo		= (ammotype_t) value; break;
    case 1:ptr -> upstate	= value; break;
    case 2:ptr -> downstate 	= value; break;
    case 3:ptr -> readystate	= value; break;
    case 4:ptr -> atkstate	= value; break;
    case 5:ptr -> flashstate	= value; break;
    default:fprintf (stderr, "Invalid Weapon record\n");
  }
  // printf ("Patched element %d of WEAPONS %d to %d\n", record, number, value);
}

/* ---------------------------------------------------------------------------- */

static unsigned int get_action_function_num (actionf_v aname)
{
  unsigned int p;

  p = 0;
  do
  {
    if (action_ptrs [p].acv == aname)
      return (p);
  } while (++p < ARRAY_SIZE (action_ptrs));

  return (0);
}

/* ---------------------------------------------------------------------------- */
/* pointer [number] (frame [record]) = frame [value] */

/* The pointer number is the n'th frame discounting the NULL pointers */

static void dh_write_to_pointer (unsigned int number, unsigned int record, unsigned int value, unsigned int line_no)
{
  int counter;
  int p,q;

  if ((value < NUMSTATES) && (record < NUMSTATES))
  {
    counter = -1;
    p = -1;

    do
    {
      p++;
      if (states_ptr_copy[p].acv) counter++;
    } while (counter < (int) number);

    if (p != record)
    {
      fprintf (stderr, "Pointer value (%u) and frame value (%u) don't agree at line %d\n", value, record, line_no-1);
      // fprintf (stderr, "counter = %d, p = %d, number = %d, record = %d, value = %d\n",
      // counter, p, number,record, value);
    }
    else
    {
      p = get_action_function_num (states_ptr_copy[record].acv);
      q = get_action_function_num (states_ptr_copy[value].acv);

      if ((action_player_type [q] != 255)
       && (action_player_type [p] != action_player_type [q]))
      {
	fprintf (stderr, "Cannot replace A_%s with A_%s at line %d\n",
		dehack_codeptr_frames [p], dehack_codeptr_frames [q], line_no-1);
      }
      else
      {
	states[record].action.acv = states_ptr_copy[value].acv;
#if 0
	printf ("Pointer copied from frame %d to %d (A_%s -> A_%s)\n",
		value, record, dehack_codeptr_frames [p], dehack_codeptr_frames [q]);
#endif
      }
    }
  }
}

/* ---------------------------------------------------------------------------- */
#ifdef CREATE_DEHACK_FILE
static void write_a_cheat (FILE * fout, unsigned int num, unsigned char * ptr, unsigned int length)
{
  unsigned int c;

  fprintf (fout, "%s = ", dehack_cheats[num]);
  while (length)
  {
    c = SCRAMBLE (*ptr);
    if ((c < 32) || (c > 126))
      length = 1;
    else
      fprintf (fout, "%c", c);
    ptr++;
    length--;
  }
  fprintf (fout, "\n");
}

static void write_all_cheats (FILE * fout)
{
  fprintf (fout, "%s %d\n", dehack_patches[8], 0);

  write_a_cheat (fout, 0, cheat_mus_seq, 8);
  write_a_cheat (fout, 1, cheat_choppers_seq, 10);
  write_a_cheat (fout, 2, cheat_god_seq, 5);
  write_a_cheat (fout, 3, cheat_ammo_seq, 5);
  write_a_cheat (fout, 4, cheat_ammonokey_seq, 4);
  write_a_cheat (fout, 5, cheat_noclip_seq, 10);
  write_a_cheat (fout, 6, cheat_commercial_noclip_seq, 6);
  write_a_cheat (fout, 7, cheat_powerup_seq[0], 9);
  write_a_cheat (fout, 8, cheat_powerup_seq[1], 9);
  write_a_cheat (fout, 9, cheat_powerup_seq[2], 9);
  write_a_cheat (fout, 10, cheat_powerup_seq[3], 9);
  write_a_cheat (fout, 11, cheat_powerup_seq[4], 9);
  write_a_cheat (fout, 12, cheat_powerup_seq[5], 9);
  write_a_cheat (fout, 13, cheat_powerup_seq[6], 8);
  write_a_cheat (fout, 14, cheat_clev_seq, 9);
  write_a_cheat (fout, 15, cheat_mypos_seq, 7);
  write_a_cheat (fout, 16, cheat_amap_seq, 4);

  fprintf (fout, "\n\n");

}
#endif
/* ---------------------------------------------------------------------------- */

static void dh_write_to_cheat (unsigned int record, char * aline)
{
  unsigned char * ptr;
  unsigned int max_length;
  unsigned int c;
  unsigned char d;

  if (M_CheckParm ("-nochangecheats"))
    return;

  ptr = 0;
  max_length = 0;

  switch (record)
  {
    case 0: //		"Change music"
      ptr = cheat_mus_seq;
      max_length = 8;
      break;

    case 1: //		"Chainsaw",
      ptr = cheat_choppers_seq;
      max_length = 10;
      break;

    case 2: //		"God mode"
      ptr = cheat_god_seq;
      max_length = 5;
      break;

    case 3: //		"Ammo & Keys"
      ptr = cheat_ammo_seq;
      max_length = 5;
      break;

    case 4: //		"Ammo"
      ptr = cheat_ammonokey_seq;
      max_length = 4;
      break;

    case 5: //		"No Clipping 1"
      ptr = cheat_noclip_seq;
      max_length = 10;
      break;

    case 6: //		"No Clipping 2"
      ptr = cheat_commercial_noclip_seq;
      max_length = 6;
      break;

    case 7: //		"Invincibility"
      ptr = cheat_powerup_seq[0];
      max_length = 9;
      break;

    case 8: //		"Berserk"
      ptr = cheat_powerup_seq[1];
      max_length = 9;
      break;

    case 9: //		"Invisibility"
      ptr = cheat_powerup_seq[2];
      max_length = 9;
      break;

    case 10://		"Radiation Suit"
      ptr = cheat_powerup_seq[3];
      max_length = 9;
      break;

    case 11://		"Auto-map"
      ptr = cheat_powerup_seq[4];
      max_length = 9;
      break;

    case 12://		"Lite-Amp Goggles"
      ptr = cheat_powerup_seq[5];
      max_length = 9;
      break;

    case 13://		"BEHOLD menu"
      ptr = cheat_powerup_seq[6];
      max_length = 8;
      break;

    case 14://		"Level Warp"
      ptr = cheat_clev_seq;
      max_length = 9;
      break;

    case 15://		"Player Position"
      ptr = cheat_mypos_seq;
      max_length = 7;
      break;

    case 16://		"Map cheat"
      ptr = cheat_amap_seq;
      max_length = 4;
      break;
  }

  c = dh_inchar (aline,'=');
  if (c)
  {
    aline += c;
    if (*aline == ' ') aline++;

    c = 0;
    while (c < max_length)
    {
      d = aline[c];
      if (d == 0)
      {
	ptr[c] = 0xff;
	return;
      }
      ptr[c] = SCRAMBLE(d);
#if 0
      if (ptr == cheat_powerup_seq[0])
      {
	cheat_powerup_seq [1][c] =
	cheat_powerup_seq [2][c] =
	cheat_powerup_seq [3][c] =
	cheat_powerup_seq [4][c] =
	cheat_powerup_seq [5][c] =
 	cheat_powerup_seq [6][c] = ptr [c];
      }
#endif
      c++;
    }
  }
}

/* ---------------------------------------------------------------------------- */
#ifdef CREATE_DEHACK_FILE
static void write_all_miscs (FILE * fout)
{
  int c;

  fprintf (fout, "%s %d\n", dehack_patches[9], 0);
  fprintf (fout, "%s = %d\n", dehack_miscs [0], Initial_Health);
  fprintf (fout, "%s = %d\n", dehack_miscs [1], Initial_Bullets);
  fprintf (fout, "%s = %d\n", dehack_miscs [2], Max_Health_200);
  fprintf (fout, "%s = %d\n", dehack_miscs [3], Max_Armour);
  fprintf (fout, "%s = %d\n", dehack_miscs [5], Green_Armour_Class);
  fprintf (fout, "%s = %d\n", dehack_miscs [7], Blue_Armour_Class);
  fprintf (fout, "%s = %d\n", dehack_miscs [9], Max_Soulsphere_Health);
  fprintf (fout, "%s = %d\n", dehack_miscs [10], Soulsphere_Health);
  fprintf (fout, "%s = %d\n", dehack_miscs [11], Megasphere_Health);
  fprintf (fout, "%s = %d\n", dehack_miscs [12], God_Mode_Health);
  fprintf (fout, "%s = %d\n", dehack_miscs [13], IDFA_Armour);
  fprintf (fout, "%s = %d\n", dehack_miscs [15], IDFA_Armour_Class);
  fprintf (fout, "%s = %d\n", dehack_miscs [17], IDKFA_Armour);
  fprintf (fout, "%s = %d\n", dehack_miscs [19], IDKFA_Armour_Class);
  fprintf (fout, "%s = %d\n", dehack_miscs [21], bfg_cells);
  if (Monsters_Infight1 == false)
    c = 202;
  else
    c = 221;
  fprintf (fout, "%s = %d\n", dehack_miscs [22], c);
  fprintf (fout, "%s = %d\n", dehack_miscs [23], Player_Jump);
  fprintf (fout, "%s = %d\n", dehack_miscs [24], Homing_Missiles);

  fprintf (fout, "\n\n");

}
#endif

/* ---------------------------------------------------------------------------- */

static void dh_write_to_misc (unsigned int number, unsigned int record, unsigned int value)
{
  switch (record)
  {
    case 0:	//	"Initial Health",
      Initial_Health = value;
      break;

    case 1:	//	"Initial Bullets",
      Initial_Bullets = value;
      break;

    case 2:	//	"Max Health",
      Max_Health_200 = value;
      break;

    case 3:	//	"Max Armor",
    case 4:	//	"Max Armour",
      Max_Armour = value;
      break;

    case 5:	//	"Green Armor Class",
    case 6:	//	"Green Armour Class",
      Green_Armour_Class = value;
      break;

    case 7:	//	"Blue Armor Class",
    case 8:	//	"Blue Armour Class",
      Blue_Armour_Class = value;
      break;

    case 9:	//	"Max Soulsphere",
      Max_Soulsphere_Health = value;
      break;

    case 10:	//	"Soulsphere Health",
      Soulsphere_Health = value;
      break;

    case 11:	//	"Megasphere Health",
      Megasphere_Health = value;
      break;

    case 12:	//	"God Mode Health",
      God_Mode_Health = value;
      break;

    case 13:	//	"IDFA Armor",
    case 14:	//	"IDFA Armour",
      IDFA_Armour = value;
      break;

    case 15:	//	"IDFA Armor Class",
    case 16:	//	"IDFA Armour Class",
      IDFA_Armour_Class = value;
      break;

    case 17:	//	"IDKFA Armor",
    case 18:	//	"IDKFA Armour",
      IDKFA_Armour = value;
      break;

    case 19:	//	"IDKFA Armor Class",
    case 20:	//	"IDKFA Armour Class",
      IDKFA_Armour_Class = value;
      break;

    case 21:	//	"BFG Cells/Shot",
      bfg_cells = value;
      break;

    case 22:	//	"Monsters Infight"
      switch (value)
      {
	case 202:Monsters_Infight1 = false; break;
	case 221:Monsters_Infight1 = true; break;
      }
      break;

    case 23:	//	"Player Jump",
      Player_Jump = value;
      break;

    case 24:	//	"Homing Missiles",
      Homing_Missiles = value;
      break;
  }
}

/* ---------------------------------------------------------------------------- */

static unsigned int dh_search_str_tab (const char * const * table, const char * ttext)
{
  unsigned int counter;
  unsigned int longest_length;
  unsigned int longest_position;
  unsigned int this_length;

  longest_length = 0;
  longest_position = -1;
  counter = 0;
  do
  {
    this_length = strlen((char*) table[counter]);
    if ((this_length > longest_length)
     && (strncasecmp (ttext, (char*) table[counter], this_length) == 0))
    {
      longest_length = this_length;
      longest_position = counter;
    }
    counter++;
  } while (table[counter]);
  return (longest_position);
}

/* ---------------------------------------------------------------------------- */

static unsigned int dh_search_str_tab_n (const char * const * table, const char * ttext, unsigned int max_length)
{
  unsigned int counter;

  counter = 0;
  do
  {
    if (strncasecmp (ttext, (char*) table[counter], max_length) == 0)
      return (counter);
    counter++;
  } while (table[counter]);
  return (-1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int dh_search_str_tab_a (const char * const * table, const char * ttext)
{
  unsigned int counter;

  counter = 0;
  do
  {
    if (strcasecmp (ttext, (char*) table[counter]) == 0)
      return (counter);
    counter++;
  } while (table[counter]);
  return (-1);
}

/* ---------------------------------------------------------------------------- */

#ifdef CREATE_DEHACK_FILE

static void write_a_text_msg (FILE * fout, char * ttext, unsigned int num)
{
  int j;
  char s1 [18*41];
  char *s2;
  const spellings_t * spell;

  strcpy (s1, ttext);
  fprintf (fout,"Message %d\n", num);

  j = ARRAY_SIZE (spelling_corrections);
  spell = spelling_corrections;
  do
  {
    dh_correct_spelling (s1, spell -> correct, spell -> wrong);
    spell++;
  } while (--j);

  s2 = s1;

  while (*s2)
  {
    if (*s2 == 10)
    {
      fprintf (fout,"\\n\n");
      s2++;
    }
    else
    {
      fprintf (fout, "%c", *s2++);
    }
  }
  fprintf (fout,"\n\n");
}

static unsigned int write_a_text_bank (FILE * fout, const char * const * table, unsigned int pos)
{
  unsigned int counter;

  counter = 0;
  do
  {
    write_a_text_msg (fout, (char*) table[counter], pos + counter);
    counter++;
  } while (table[counter]);
  return (pos + counter);
}

static void write_all_texts (FILE * fout)
{
  unsigned int counter;
  unsigned int pos;
  unsigned int episode;
  unsigned int map;
  char * s;

  counter = 0;

  //counter = write_a_text_bank (fout, (const char **)mapnames, counter);
  //counter = write_a_text_bank (fout, (const char **)mapnames2, counter);
  //counter = write_a_text_bank (fout, (const char **)mapnamest, counter);
  //counter = write_a_text_bank (fout, (const char **)mapnamesp, counter);

  episode = 1;
  do
  {
    map = 1;
    do
    {
      s = *(HU_access_mapname_E (episode,map));
      if ((s) && (*s))
      {
	write_a_text_msg (fout, s, counter);
	counter++;
      }
    } while (++map < 10);
  } while (++episode < 5);

  map = 1;
  do
  {
    s = *(HU_access_mapname_E (255,map));
    if ((s) && (*s))
    {
      write_a_text_msg (fout, s, counter);
      counter++;
    }
  } while (++map < 33);

  map = 1;
  do
  {
    s = *(HU_access_mapname_E (254,map));
    if ((s) && (*s))
    {
      write_a_text_msg (fout, s, counter);
      counter++;
    }
  } while (++map < 33);

  map = 1;
  do
  {
    s = *(HU_access_mapname_E (253,map));
    if ((s) && (*s))
    {
      write_a_text_msg (fout, s, counter);
      counter++;
    }
  } while (++map < 33);

  counter = write_a_text_bank (fout, (const char **)finale_messages, counter);
  counter = write_a_text_bank (fout, (const char **)finale_backdrops, counter);
  counter = write_a_text_bank (fout, (const char **)got_messages, counter);
  counter = write_a_text_bank (fout, (const char **)dmain_messages, counter);
  counter = write_a_text_bank (fout, (const char **)menu_messages, counter);
  counter = write_a_text_bank (fout, (const char **)endmsg, counter);
  counter = write_a_text_bank (fout, (const char **)door_messages, counter);
  counter = write_a_text_bank (fout, (const char **)am_map_messages, counter);
  counter = write_a_text_bank (fout, (const char **)stat_bar_messages, counter);
  counter = write_a_text_bank (fout, (const char **)special_effects_messages, counter);
  counter = write_a_text_bank (fout, (const char **)sound_names_copy, counter);
  counter = write_a_text_bank (fout, (const char **)music_names_copy, counter);
  counter = write_a_text_bank (fout, (const char **)sprnames_orig, counter);

  pos = 0;
  do
  {
    write_a_text_msg (fout, castorder[pos].name, counter);
    counter++;
    pos++;
  } while (castorder[pos].name);
}
#endif

/* ---------------------------------------------------------------------------- */

static unsigned int replace_text_levelx (char * orig, char * newt)
{
  unsigned int n;

  if ((dh_strcmp (orig, "level ") == 0)
   && ((n = atoi (&orig[6])) < 100))
  {
    *(HU_access_mapname_E (255, n)) = newt;
    *(HU_access_mapname_E (254, n)) = newt; // Do TNT and Plutonia as well for completeness...
    *(HU_access_mapname_E (253, n)) = newt;
    mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
    return (0);
  }
  else
  {
    return (1);
  }
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_text_exmx (char * orig, char * newt)
{
  if ((orig[0] == 'E')
   && (orig[2] == 'M')
   && (orig[1] >= '0')
   && (orig[1] <= '9')
   && (orig[3] >= '0')
   && (orig[3] <= '9')
   && (orig[4] == ':'))
  {
    *(HU_access_mapname_E (orig[1]-'0', orig[3]-'0')) = newt;
    mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
    return (0);
  }
  else
  {
    return (1);
  }
}

/* ---------------------------------------------------------------------------- */

static int is_all_spaces (const char * text)
{
  char cc;

  do
  {
    cc = *text++;
    if (cc == 0)
      return (1);
  } while (cc == ' ');

  return (0);
}

/* ---------------------------------------------------------------------------- */

/* I've changed the spellings here, so only compare the first few characters */


static unsigned int replace_finale_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_n ((const char **)finale_messages_orig, orig, 39);
  if (counter != -1)
  {
    finale_messages [counter] = newt;
    finale_message_changed = (boolean)((int)finale_message_changed|(int)dh_changing_pwad);
    return (0);
  }

  counter = dh_search_str_tab_a ((const char **)finale_backdrops_orig, orig);
  if (counter != -1)
  {
    finale_backdrops [counter] = newt;
    return (0);
  }

  counter = dh_search_str_tab_a ((const char **)cast_names_copy, orig);
  if (counter != -1)
  {
    if (is_all_spaces (newt))
      newt [0] = 0;
    castorder[counter].name = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_got_messages_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)got_messages_orig, orig);
  if (counter != -1)
  {
    got_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int dh_match_length (const char * s1, const char * s2)
{
  char c,c1,c2;
  unsigned int count;

  /* printf ("Compared %s with %s", s1, s2); */

  count = 0;
  do
  {
    c = *s1++;
    c1 = tolower(c);
    c = *s2++;
    c2 = tolower (c);
    if (c1 != c2)
      break;
    count++;
  } while (c1);

  /* printf (" and returned %d\n", result); */
  return (count);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_startup_text (char * orig, char * newt)
{
  unsigned int i;
  unsigned int max;
  unsigned int max_pos;
  unsigned int counter;
  char * oldd;

  /* Miss out the leading spaces and limit the number of characters checked */

  while ((*orig == ' ') || (*orig == '='))
    orig++;

  counter = 0;
  max = 0;
  do
  {
    oldd = dmain_messages_orig [counter];
    while ((*oldd == ' ') || (*oldd == '='))
      oldd++;

    i = dh_match_length (orig, oldd);
    if (i > max)
    {
      max = i;
      max_pos = counter;
    }
    counter++;
  } while (dmain_messages_orig [counter]);

  if (max > 20)
  {
    dmain_messages [max_pos] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_menu_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)menu_messages_orig, orig);
  if (counter != -1)
  {
    menu_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_quit_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)endmsg_orig, orig);
  if (counter != -1)
  {
    endmsg [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_door_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)door_messages_orig, orig);
  if (counter != -1)
  {
    door_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_saveg_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)save_game_messages_orig, orig);
  if (counter != -1)
  {
    save_game_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_maptable_text (char * orig, char * newt)
{
  unsigned int episode;
  unsigned int map;
  const char * pp;
  map_dests_t * map_dests_ptr;

  pp = NULL;

  if (strcasecmp (orig, sky_1) == 0)
    pp = sky_1;
  else if (strcasecmp (orig, sky_2) == 0)
    pp = sky_2;
  else if (strcasecmp (orig, sky_3) == 0)
    pp = sky_3;
  else if (strcasecmp (orig, sky_4) == 0)
    pp = sky_4;
  else if (strcasecmp (orig, wilv) == 0)
    pp = wilv;
  else if (strcasecmp (orig, cwilv) == 0)
    pp = cwilv;
  else if (strcasecmp (orig, enterpic_1) == 0)
    pp = enterpic_1;
  else if (strcasecmp (orig, enterpic_2) == 0)
    pp = enterpic_2;
  else if (strcasecmp (orig, borderpatch_1) == 0)
    pp = borderpatch_1;
  else if (strcasecmp (orig, borderpatch_2) == 0)
    pp = borderpatch_2;

  if (pp == NULL)
    return (1);

  episode = 1;
  do
  {
    map = 0;
    do
    {
      map_dests_ptr = G_Access_MapInfoTab_E (episode, map);
      if (map_dests_ptr)
      {
	if (pp == map_dests_ptr -> sky)
	  map_dests_ptr -> sky = newt;
	if (pp == map_dests_ptr -> titlepatch)
	  map_dests_ptr -> titlepatch = newt;
	if (pp == map_dests_ptr -> enterpic)
	  map_dests_ptr -> enterpic = newt;
	if (pp == map_dests_ptr -> exitpic)
	  map_dests_ptr -> exitpic = newt;
	if (pp == map_dests_ptr -> bordertexture)
	  map_dests_ptr -> bordertexture = newt;
      }
    } while (++map < 10);
  } while (++episode < 10);

  map = 0;
  do
  {
    map_dests_ptr = G_Access_MapInfoTab_E (255, map);
    if (map_dests_ptr)
    {
      if (pp == map_dests_ptr -> sky)
	map_dests_ptr -> sky = newt;
      if (pp == map_dests_ptr -> titlepatch)
	map_dests_ptr -> titlepatch = newt;
      if (pp == map_dests_ptr -> enterpic)
	map_dests_ptr -> enterpic = newt;
      if (pp == map_dests_ptr -> exitpic)
	map_dests_ptr -> exitpic = newt;
      if (pp == map_dests_ptr -> bordertexture)
	map_dests_ptr -> bordertexture = newt;
    }
  } while (++map < 100);

  return (0);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_am_map_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)am_map_messages_orig, orig);
  if (counter != -1)
  {
    am_map_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_stat_bar_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)stat_bar_messages_orig, orig);
  if (counter != -1)
  {
    stat_bar_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_special_fx_text (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)special_effects_messages_orig, orig);
  if (counter != -1)
  {
    special_effects_messages [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_sound_fx_text (char * orig, char * newt)
{
  unsigned int counter;

  /* Search for the sound string in the copy table */

  counter = dh_search_str_tab_a ((const char **)sound_names_copy, orig);
  if ((counter != -1) && (counter > 0))
  {
    // printf ("Replaced %s (%s) with %s\n", S_sfx[counter].name, orig, newt);
    S_sfx[counter].name = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_music_fx_text (char * orig, char * newt)
{
  unsigned int counter;

  /* Search for the music string in the copy table */

  counter = dh_search_str_tab_a ((const char **)music_names_copy, orig);
  if ((counter != -1) && (counter > 0))
  {
    // printf ("Replaced %s (%s) with %s\n", S_music[counter].name, orig, newt);
    S_music[counter].name = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_chat_messages (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)chat_macros_orig, orig);
  if (counter != -1)
  {
    chat_macros [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_player_names (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)player_names_orig, orig);
  if (counter != -1)
  {
    player_names [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static unsigned int replace_sprite_names (char * orig, char * newt)
{
  unsigned int counter;

  counter = dh_search_str_tab_a ((const char **)sprnames_orig, orig);
  if (counter != -1)
  {
    sprnames [counter] = newt;
    return (0);
  }

  return (1);
}

/* ---------------------------------------------------------------------------- */

static void replace_text_string (char ** ptr, char * newt)
{
  char cc;
  char * newm;
  char * p1;
  unsigned int len;

  len = strlen (newt);
  if (len == 0)
  {
    *ptr = "";
    return;
  }

  newm = malloc (len + 10);
  if (newm)
  {
    /* Need to find '\n' sequences and swap */
    //strcpy (newm, newt);
    p1 = newm;
    do
    {
      cc = *newt++;
      if (cc == '\\')
      {
	cc = *newt++;
	switch (cc)
	{
	  case 'n': cc = '\n'; break;
	  case 'r': cc = '\r'; break;
	  case 't': cc = '\t'; break;
	}
      }
      *p1++ = cc;
    } while (cc);

    dh_remove_americanisms (newm);

    if ((*ptr != NULL)
     && (strcasecmp (*ptr, newm) == 0))	// Did it change?
    {
      // printf ("%s is unchanged\n", newm);
      free (newm);
    }
    else
    {
      // printf ("%s set\n", newm);
      // printf ("Changed '%s' to '%s'\n", *ptr, newm);
      *ptr = newm;
    }
  }
}

/* ---------------------------------------------------------------------------- */

static char ** DH_Find_language_text (char * ttext, boolean Changing)
{
  unsigned int	counter1;

  counter1 = dh_search_str_tab_a (dehack_playernames, ttext);
  if (counter1 != -1)
    return (&player_names[counter1]);

  counter1 = dh_search_str_tab_a (stat_bar_message_names, ttext);
  if (counter1 != -1)
  {
    return (&stat_bar_messages[counter1]);
  }

  counter1 = dh_search_str_tab_a (am_map_message_names, ttext);
  if (counter1 != -1)
  {
    return (&am_map_messages[counter1]);
  }

  counter1 = dh_search_str_tab_a (menu_message_names, ttext);
  if (counter1 != -1)
  {
    return (&menu_messages[counter1]);
  }

  if (strncasecmp (ttext, "HUSTR_CHATMACRO", 15) == 0)
  {
    counter1 = atoi (ttext+15);
    return (&chat_macros[counter1]);
  }

  if (strncasecmp (ttext, "HUSTR_EPI", 9) == 0)
  {
    counter1 = ttext [9] - '0';
    if (counter1 < 10)
    {
      return (&episode_names[counter1]);
      // printf ("Episode %u name is %s\n", counter1, episode_names[counter1]);
    }
  }

#if 0
  if (strcasecmp (ttext, "HUSTR_MSGU") == 0)
  {
    // return (????);
  }
#endif

  if ((strncasecmp (ttext, "HUSTR_E", 7) == 0)
   && (ttext [8] == 'M'))
  {
    mapnameschanged = (boolean)((int)mapnameschanged|(int)Changing);
    return (HU_access_mapname_E (ttext[7]-'0', ttext[9]-'0'));
  }

  if ((strncasecmp (ttext, "HUSTR_", 6) == 0)
   && (ttext[6] >= '0')
   && (ttext[6] <= '9'))
  {
    mapnameschanged = (boolean)((int)mapnameschanged|(int)Changing);
    counter1 = atoi (ttext+6);
    return (HU_access_mapname_E (255, counter1));
//  return (HU_access_mapname_E (254, counter1));
//  return (HU_access_mapname_E (253, counter1)); // Do TNT and Plutonia as well for completeness...
  }

  if ((strncasecmp (ttext, "PHUSTR_", 7) == 0)
   && (ttext[7] >= '0')
   && (ttext[7] <= '9'))
  {
    mapnameschanged = (boolean)((int)mapnameschanged|(int)Changing);
    counter1 = atoi (ttext+7);
    return (HU_access_mapname_E (254, counter1));
  }

  if ((strncasecmp (ttext, "THUSTR_", 7) == 0)
   && (ttext[7] >= '0')
   && (ttext[7] <= '9'))
  {
    mapnameschanged = (boolean)((int)mapnameschanged|(int)Changing);
    counter1 = atoi (ttext+7);
    return (HU_access_mapname_E (253, counter1));
  }

  if (strncasecmp (ttext, "STARTUP", 7) == 0)
  {
    ttext += 7;
    if (strncasecmp (ttext, "TITLE", 5) == 0)
      return (&dmain_messages [D_Startup_msg_number ()]);
    if ((ttext [0] >= '0')
     && (ttext [0] <= '9'))
    {
      counter1 = atoi (ttext);
      if (counter1 <= 9)
        return (&startup_messages [counter1]);
    }
    return (NULL);
  }

  if (strcasecmp (ttext, "GGSAVED") == 0)
  {
    return (&save_game_messages[GG_GGSAVED]);
  }

  if (strcasecmp (ttext, "SAVEGAMENAME") == 0)
  {
    return (&save_game_messages[GG_SAVEGAMENAME]);
  }

  if ((strcasecmp (ttext+2, "TEXT") == 0)
   && ((counter1 = ttext [1]) >= '0')
   && (counter1 <= '9'))
  {
    switch (toupper (ttext[0]))
    {
      case 'E':
	finale_message_changed = (boolean)((int)finale_message_changed|(int)Changing);
	return (&finale_messages[counter1-'0'+e0text]);

      case 'C':
	if ((counter1 >= '1')
	 && (counter1 <= '6'))
	{
	  finale_message_changed = (boolean)((int)finale_message_changed|(int)Changing);
	  return (&finale_messages[counter1-'1'+c1text]);
	}
	break;

      case 'P':
	if ((counter1 >= '1')
	 && (counter1 <= '6'))
	{
	  finale_message_changed = (boolean)((int)finale_message_changed|(int)Changing);
	  return (&finale_messages[counter1-'1'+p1text]);
	}
	break;

      case 'T':
	if ((counter1 >= '1')
	 && (counter1 <= '6'))
	{
	  finale_message_changed = (boolean)((int)finale_message_changed|(int)Changing);
	  return (&finale_messages[counter1-'1'+t1text]);
	}
	break;
    }
  }

  if (strcasecmp (ttext, "BGFLAT06") == 0)
  {
    return (&finale_backdrops[BG_SLIME16]);
  }

  if (strcasecmp (ttext, "BGFLAT11") == 0)
  {
    return (&finale_backdrops[BG_RROCK14]);
  }

  if (strcasecmp (ttext, "BGFLAT20") == 0)
  {
    return (&finale_backdrops[BG_RROCK07]);
  }

  if (strcasecmp (ttext, "BGFLAT30") == 0)
  {
    return (&finale_backdrops[BG_RROCK17]);
  }

  if (strcasecmp (ttext, "BGFLAT15") == 0)
  {
    return (&finale_backdrops[BG_RROCK13]);
  }

  if (strcasecmp (ttext, "BGFLAT31") == 0)
  {
    return (&finale_backdrops[BG_RROCK19]);
  }

  counter1 = dh_search_str_tab_a (dehack_monster_obit_strings, ttext);
  if ((counter1 != -1)
   && (counter1 < (ARRAY_SIZE(dehack_cast_strings)-1)))
  {
    return (&castorder[counter1].obit);
  }

  counter1 = dh_search_str_tab_a (dehack_other_obit_strings, ttext);
  if (counter1 != -1)
  {
    return (&obituary_messages[counter1]);
  }

  if (strncasecmp (ttext, "QUITMSG", 7) == 0)
  {
    counter1 = atoi (ttext+7);
    if (counter1 < 30)			// Hard coded size, bad!
    {
      if (counter1 >= qty_endmsg_nums)
	qty_endmsg_nums = counter1 + 1;
      return (&endmsg[counter1]);
    }
  }

  /* We use the dh_search_str_tab (best match) here because */
  /* freedoom uses GOTREDSKULL and harmony uses GOTREDSKUL */
  counter1 = dh_search_str_tab (dehack_got_strings, ttext);
  if (counter1 != -1)
  {
    return (&got_messages[counter1]);
  }

  counter1 = dh_search_str_tab_a (dehack_require_key_strings, ttext);
  if (counter1 != -1)
  {
    return (&door_messages[counter1]);
  }

  counter1 = dh_search_str_tab_a (dehack_cast_strings, ttext);
  if (counter1 != -1)
  {
    return (&castorder[counter1].name);
  }

  return (NULL);
}

/* ---------------------------------------------------------------------------- */

static unsigned int DH_Parse_language_string (char * a_line)
{
  unsigned int	counter1;
  unsigned int	counter2;
  char		cc;
  char *	string1;
  char **	dest;
  char		first_word [50];

  switch (a_line [0])
  {
    case 0:
    case '#':
    case '/':
      return (0);
  }

  counter2 = dh_inchar (a_line, '=');
  if (counter2 == 0)
    return (-1);

  string1 = a_line + counter2;
  while (*string1 == ' ')
    string1++;

  counter2 = 0;
  do
  {
    cc = a_line [counter2];
    if ((cc <= ' ') || (counter2 >= (sizeof (first_word)-2)))
      cc = 0;
    first_word [counter2++] = cc;
  } while (cc);

  if (*string1 == '\"')
  {
    counter1 = strlen (string1);
    do
    {
      cc = string1 [counter1];
      string1 [counter1] = 0;
      counter1--;
    } while ((counter1) && (cc != '\"'));
    string1++;
  }

  if (is_all_spaces (string1))
    string1 [0] = 0;

  dest = DH_Find_language_text (first_word, dh_changing_pwad);
  if (dest)
  {
    // printf ("Replaced (%s) with (%s)\n", first_word,string1);
    replace_text_string (dest, string1);
    return (0);
  }

  return (-1);
}

/* ---------------------------------------------------------------------------- */

void DH_parse_hacker_file_f (const char * filename, FILE * fin, unsigned int filetop_pos)
{
  char		a_line [2048];
  dhjobs_t	current_job;
  unsigned int	job_params[2];
  unsigned int	params[2];
  unsigned int	counter1;
  unsigned int	counter2;
  char		cc;
  char *	string1;
  char *	string2;
  unsigned int  dh_line_number;


  if (fin)
  {
    dh_line_number = 0;
    current_job = JOB_NULL;
    do
    {
      dh_fgets_x (a_line, sizeof (a_line) - 4, fin, filetop_pos);
      dh_line_number++;
      if (a_line [0] == '#')
	continue;

      /* Find the numbers in the line */
      params[0] =
      params[1] =
      counter2  = 0;

      /* If there's an = in the line start from there */
      counter1 = dh_inchar (a_line, '=');

      do
      {
	cc = a_line [counter1++];
	if (((cc >= '0') && (cc <= '9')) || (cc == '-'))
	{
	  params[counter2] = atoi (&a_line[counter1-1]);
	  counter2++;

	  do
	  {
	    cc = a_line [counter1++];
	  } while (((cc >= '0') && (cc <= '9')) || (cc == '-'));
	}

      } while ((cc) && (counter2 < 2));

      counter1 = dh_search_str_tab (dehack_patches, a_line);
      if ((counter1 == 0) || ((counter1 != -1) && (dh_inchar(a_line,'=') == 0)))
      {
	switch (counter1)
	{
	  case JOB_END:
	    return;

	  case JOB_NULL:
	  case JOB_CODEPTR:
	  case JOB_STRINGS:
	  case JOB_PARS:
	  case JOB_SPRITE:
	  case JOB_CHEAT:
	  case JOB_MISC:
	    current_job = (dhjobs_t) counter1;
	    break;

	  case JOB_THING:
	    if ((params[0] >=1) && (params[0] <= NUMMOBJTYPES))
	    {
	      current_job = JOB_THING;
	      job_params[0] = params[0];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Thing number (%d) at line %d\n",
	  			     params[0],dh_line_number);
	    }
	    break;

	  case JOB_SOUND:
	    if (params[0] < NUMSFX)
	    {
	      current_job = JOB_SOUND;
	      job_params[0] = params[0];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Sound number (%d) at line %d\n",
	  			     params[0],dh_line_number);
	    }
	    break;

	  case JOB_FRAME:
	    if (params[0] < NUMSTATES)
	    {
	      current_job = JOB_FRAME;
	      job_params[0] = params[0];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Frame number (%d) at line %d\n",
	  			     params[0],dh_line_number);
	    }
	    break;

	  case JOB_AMMO:
	    if (params[0] < 4)
	    {
	      current_job = JOB_AMMO;
	      job_params[0] = params[0];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Ammo number (%d) at line %d\n",
	  			     params[0],dh_line_number);
	    }
	    break;

	  case JOB_WEAPON:
	    if (params[0] < NUMWEAPONS)
 	    {
	      current_job = JOB_WEAPON;
	      job_params[0] = params[0];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Weapon number (%d) at line %d\n",
	  			     params[0], dh_line_number);
	    }
	    break;

	  case JOB_POINTER:
	    if (params[0] < 448)
 	    {
	      current_job = JOB_POINTER;
	      job_params[0] = params[0];
	      job_params[1] = params[1];
	    }
	    else
	    {
	      current_job = JOB_NULL;
	      fprintf (stderr, "DeHackEd: Invalid Pointer number (%d) at line %d\n",
	  			     params[0], dh_line_number);
	    }
	    break;

	  case JOB_TEXT:
	    current_job = JOB_TEXT;
	    job_params[0] = params[0];
	    job_params[1] = params[1];

	    /* job_params[0] is the length of the first text message */
	    /* job_params[1] is the length of the replacement text message */

	    /* We alloc some extra to allow for american/british spelling changes */
	    string1 = malloc (job_params[0]+12);
	    string2 = malloc (job_params[1]+12);
	    if ((string1) && (string2))
	    {
	      /* Cannot use fread because doesn't convert dos files!! */
	      // fread(string1, 1, job_params[0], fin);
	      // fread(string2, 1, job_params[1], fin);

	      counter2 = dh_line_number;  /* Remember where the line number was */

	      counter1 = 0;
	      do
	      {
		string1 [counter1] = cc = fgetc (fin);
		if (cc != 13) counter1++;
		if (cc == 10) dh_line_number++;
	      } while (counter1 < job_params[0]);

	      counter1 = 0;
	      do
	      {
		string2 [counter1] = cc = fgetc (fin);
		if (cc != 13) counter1++;
		if (cc == 10) dh_line_number++;
	      } while (counter1 < job_params[1]);

	      string1 [job_params[0]] = 0;
	      string2 [job_params[1]] = 0;

	      // printf ("STRING1 = %s\n", string1);
	      // printf ("STRING2 = %s\n", string2);

	      dh_remove_americanisms (string1);
	      dh_remove_americanisms (string2);

	      if (replace_text_exmx (string1, string2))
	      if (replace_text_levelx (string1, string2))
	      if (replace_finale_text (string1, string2))
	      if (replace_got_messages_text (string1, string2))
	      if (replace_startup_text (string1, string2))
	      if (replace_menu_text (string1, string2))
	      if (replace_quit_text (string1, string2))
	      if (replace_door_text (string1, string2))
	      if (replace_saveg_text (string1, string2))
	      if (replace_maptable_text (string1, string2))
	      if (replace_am_map_text (string1, string2))
	      if (replace_stat_bar_text (string1, string2))
	      if (replace_special_fx_text (string1, string2))
	      if (replace_sound_fx_text (string1, string2))
	      if (replace_music_fx_text (string1, string2))
	      if (replace_chat_messages (string1, string2))
	      if (replace_player_names (string1, string2))
	      if (replace_sprite_names (string1, string2))
	      {
		if (M_CheckParm ("-showunknown"))
		  fprintf (stderr, "DeHackEd:Failed to match text at line %d\n%s\n%s", counter2,string1,string2);
		free (string2);
	      }
	      free (string1);
	    }
	    else /* Malloc failed, by pass text */
	    {
	      if (string1) free (string1);
	      if (string2) free (string2);
	      fseek (fin, (long) (job_params[0] + job_params[1]), SEEK_CUR);
	    }
	    break;
	}   /* of switch */
      }
      else  /* Not a new job type, continue with previous */
      {
	switch (current_job)
	{
	  case JOB_NULL:
	    counter1 = 0; //dh_search_str_tab (dehack_info, a_line);
	    // if (counter1 != -1)
	    //  dh_write_to_???? (job_params[0], counter1, params[0]);
	    break;

	  case JOB_THING:
	    counter1 = dh_search_str_tab (dehack_things, a_line);
	    if (counter1 != -1)
	    {
	      switch (counter1)
	      {
		case 21:				// Writing to "bits"
		  counter2 = dh_inchar (a_line, '=');
		  if (counter2)
		  {
		    string1 = next_arg (a_line+counter2);
		    if (string1[0] >= 'A')		// and symbolic bits?
		      decode_things_bits (params, string1);
		  }
		  break;

		case 23:				// Writing to "scale"
		  counter2 = dh_inchar (a_line, '=');
		  if (counter2)
		  {
		    float arg;
		    string1 = next_arg (a_line+counter2);
		    arg = (float) atof (string1);
		    arg = arg * (FRACUNIT);
		    params [0] = (int)arg;
		  }
		  break;
	      }
	      dh_write_to_thing (job_params[0], counter1, params[0]);
	    }
	    break;

	  case JOB_SOUND:
	    counter1 = dh_search_str_tab (dehack_sounds, a_line);
	    if (counter1 != -1)
	      dh_write_to_sound (job_params[0], counter1, params[0]);
	    break;

	  case JOB_FRAME:
	    counter1 = dh_search_str_tab (dehack_frames, a_line);
	    if (counter1 != -1)
	      dh_write_to_frame (job_params[0], counter1, params[0]);
	    break;

	  case JOB_SPRITE:
	    counter1 = dh_search_str_tab (dehack_sprites, a_line);
	    if (counter1 != -1)
	      dh_write_to_sprite (job_params[0], counter1, params[0]);
	    break;

	  case JOB_AMMO:
	    counter1 = dh_search_str_tab (dehack_ammos, a_line);
	    if (counter1 != -1)
	      dh_write_to_ammo (job_params[0], counter1, params[0]);
	    break;

	  case JOB_WEAPON:
	    counter1 = dh_search_str_tab (dehack_weapons, a_line);
	    if (counter1 != -1)
	      dh_write_to_weapon (job_params[0], counter1, params[0]);
	    break;

	  case JOB_POINTER:
	    counter1 = dh_search_str_tab (dehack_pointers, a_line);
	    if (counter1 != -1)
	      dh_write_to_pointer (job_params[0], job_params[1], params[0], dh_line_number);
	    break;

	  case JOB_CHEAT:
	    counter1 = dh_search_str_tab (dehack_cheats, a_line);
	    if (counter1 != -1)
	      dh_write_to_cheat (counter1, a_line);
	    break;

	  case JOB_MISC:
	    counter1 = dh_search_str_tab (dehack_miscs, a_line);
	    if (counter1 != -1)
	      dh_write_to_misc (job_params[0], counter1, params[0]);
	    break;

	  case JOB_PARS:
	    if (strncasecmp (a_line, "par ", 4) == 0)	// Par nn pp (no = sign!)
	    {
	      unsigned int ptime;
	      map_dests_t * mapd_ptr;

	      string1 = next_arg (a_line);
	      while (((cc = *string1) != 0) && ((cc < '0') || (cc > '9'))) string1++;
	      if (gamemode == commercial)
	      {
		counter1 = 255;
	      }
	      else
	      {
		counter1 = atoi (string1);
		while (((cc = *string1) >= '0') && (cc <= '9')) string1++;
		while (((cc = *string1) != 0) && ((cc < '0') || (cc > '9'))) string1++;
	      }
	      counter2 = atoi (string1);

	      mapd_ptr = G_Access_MapInfoTab_E (counter1, counter2);
	      string1 = next_arg (string1);
	      while (((cc = *string1) != 0) && ((cc < '0') || (cc > '9'))) string1++;
	      ptime = atoi (string1);
	      while (((cc = *string1) >= '0') && (cc <= '9')) string1++;
	      if (*string1 == ':')
		ptime=(ptime*60)+atoi(string1+1);
	      ptime = (ptime + 4) / 5;
	      if (ptime > 255) ptime = 255;
	      mapd_ptr -> par_time_5 = ptime;
	      // printf ("Par %u,%u = %u (%u)\n", counter1, counter2,mapd_ptr -> par_time_5,ptime*5);
	      par_changed = (boolean)((int)par_changed|(int)dh_changing_pwad);
	      counter1 = 0;
	    }
	    break;

	  case JOB_CODEPTR:
	    counter2 = dh_inchar (a_line, '=');
	    if (counter2 == 0)
	      break;

	    string1 = a_line + counter2;
	    while (*string1 == ' ')
	      string1++;

	    counter2 = dh_inchar (a_line, ' ');
	    if (counter2 == 0)
	      break;

	    counter2 = atoi (a_line + counter2);

	    counter1 = dh_search_str_tab (dehack_codeptrs, a_line);
	    if (counter1 != -1)
	    {
	      /* The docs say that the "A_" at the start of each name */
	      /* isn't used, however they're there in secur.wad */
	      if (strncasecmp (string1, "A_", 2) == 0)
		string1 += 2;
	      counter1 = dh_search_str_tab_a (dehack_codeptr_frames, string1);
	      if (counter1 != -1)
	      {
		unsigned int p;
		p = get_action_function_num (states[counter2].action.acv);

		if ((action_player_type [counter1] != 255)
		 && (action_player_type [p] != action_player_type [counter1]))
		{
		  fprintf (stderr, "Cannot replace A_%s with A_%s at line %d\n",
			dehack_codeptr_frames [p], dehack_codeptr_frames [counter1], dh_line_number-1);
		}
		else
		{
		  states[counter2].action.acv = action_ptrs[counter1].acv;
		  // printf ("Frame %u set to %s\n", counter2, dehack_codeptr_frames [counter1]);
		}
	      }
	    }
	    break;

	  case JOB_STRINGS:
	    /* Freedoom has a trailing backslash at the end of the line */
	    /* to signify that the next line continues. */
	    do
	    {
	      counter1 = strlen (a_line);
	      if ((counter1 == 0)
	       || (a_line [counter1 - 1] != '\\'))
		break;

	      dh_fgets_x (a_line+(counter1-1), (sizeof (a_line) - 4)-counter1, fin, filetop_pos);
	      dh_line_number++;
	      if ((a_line [counter1-1] == ' ')
	       || (a_line [counter1-1] == '\t'))
	      {
		counter2 = counter1 - 1;
		do
		{
		  counter2++;
		} while ((a_line [counter2] == ' ')
		      || (a_line [counter2] == '\t'));
		strcpy (a_line + (counter1-1), a_line + counter2);
	      }
	    } while (1);
	    counter1 = DH_Parse_language_string (a_line);
	    break;
	}
	if ((counter1 == -1) && (*a_line)
	 && (M_CheckParm ("-showunknown")))
	  fprintf (stderr,"DeHackEd:Failed to find \"%s\" at line %d of file %s (job %u)\n", a_line, dh_line_number, filename, current_job);
      }
    } while (dh_feof(fin,filetop_pos)==0);
  }
}

/* ---------------------------------------------------------------------------- */

/* Why all this palavar opening files? */
/* because there's a bug in the Acorn fgetc library call which */
/* can't cope with a file being closed and then immediately reopened */
/* under certain strange circumstances! */

void DH_parse_hacker_file (const char * filename)
{
  FILE * fin;

  fin = fopen (filename, "r");
  if (fin)
  {
    DH_parse_hacker_file_f (filename, fin, ~0);
    fclose (fin);
  }
  else
  {
    fprintf (stderr, "DeHackEd:Cannot open file %s\n", filename);
  }

#ifdef CREATE_DEHACK_FILE
  fin = fopen ("<DeHack$Dir>.Resources.DeHack/Deh", "w");
  if (fin)
  {
    fprintf (fin, "Patch File for DeHackEd v3.0\n");
    fprintf (fin, "Doom version = 21\n");
    fprintf (fin, "Patch format = 6\n\n");

    write_all_things (fin);
    write_all_sounds (fin);
    write_all_frames (fin);
    // write_all_sprites (fin);
    write_all_ammos (fin);
    write_all_weapons (fin);
    // write_all_pointers (fin);
    write_all_cheats (fin);
    write_all_miscs (fin);
    write_all_texts (fin);
    fclose (fin);
  }
#endif
}

/* ---------------------------------------------------------------------------- */

void DH_parse_language_file_f (const char * filename, FILE * fin, unsigned int filetop_pos)
{
  char		cc;
  char		a_line [1024];
  char		next_line [1024];
  unsigned int	counter1;
  unsigned int	counter2;
  unsigned int  dh_line_number;

  if (fin)
  {
    dh_line_number = 0;
    next_line [0] = 0;
    do
    {

/*
	Harmony.wad has lines like:

E1TEXT =
	"line 1\n"
	"line 2\n"
*/
      if (next_line [0])
      {
	strncpy (a_line, next_line, 1020);
      }
      else
      {
	dh_fgets_x (a_line, 1020, fin, filetop_pos);
	dh_line_number++;
      }

      do
      {
	dh_fgets_x (next_line, 1020, fin, filetop_pos);
	dh_line_number++;

	counter1 = 0;
	while ((next_line[counter1]) && (next_line[counter1] <= ' ')) counter1++;
	if (next_line [counter1] != '"')
	  break;

	// printf ("Continuation line found - %s\n", next_line);
	counter2 = strlen (a_line);
	while (counter2)
	{
	  cc = a_line [--counter2];
	  if (cc == '=')
	  {
	    counter2++;
	    a_line [counter2++] = ' ';
	    a_line [counter2++] = '"';
	    break;
	  }
	  if (cc == '"')
	  {
	    //a_line [counter2++] = '\\';
	    //a_line [counter2++] = 'n';
	    break;
	  }
	}

	strcpy (a_line+counter2,next_line+counter1+1);
      } while (1);

      // printf ("Language %s\n", a_line);
      counter1 = DH_Parse_language_string (a_line);
#if 1
      if ((counter1 == -1) && (*a_line)
       && (M_CheckParm ("-showunknowntext")))
	fprintf (stderr,"DeHackEd:Failed to find \"%s\" at line %d of file %s\n", a_line, dh_line_number, filename);
#endif
    } while ((next_line[0]) || (dh_feof(fin,filetop_pos)==0));
  }
}

/* ---------------------------------------------------------------------------- */

void DH_replace_file_extension (char * newname, const char * oldname, char * n_ext)
{
  unsigned int p;
  unsigned int q;
  DIR * dirp;
  struct dirent *dp;
  char * leaf;
  char buffer [200];

  p = 0;
  q = -1;

  while (oldname [p])
  {
    switch (oldname [p])
    {
      case EXTSEPC:
	q = p;
	break;

      case DIRSEPC:
#ifndef __riscos
      case '\\':
#endif
	q = -1;
    }
    newname [p] = oldname [p];
    p++;
  }

  if (q == -1)  q = p;

  newname [q] = EXTSEPC;
  strcpy (newname+q+1, n_ext);

//printf ("filename %s is now %s\n", oldname, newname);

  /* On a case dependent file system we need to get it right! */

  dirname (buffer, newname);
  dirp = opendir (buffer);
  if (dirp)
  {
    leaf = (char *) leafname (newname);
    while ((dp = readdir (dirp)) != NULL)
    {
      if (strcasecmp (leaf, dp -> d_name) == 0)
      {
	sprintf (newname, "%s"DIRSEP"%s", buffer, dp -> d_name);
	break;
      }
    }
    closedir (dirp);
  }

//printf ("filename %s is now %s\n", oldname, newname);
}

/* ---------------------------------------------------------------------------- */

void DH_parse_hacker_wad_file (const char * wadname, boolean do_it)
{
  char aline [28];
  char dehname [250];
  FILE * fin;

  /* Change /WAD to /BEX */
  DH_replace_file_extension (dehname, wadname, "bex");
  fin = fopen (dehname, "r");
  if (fin == NULL)
  {
    /* Change /WAD to /DEH */
    DH_replace_file_extension (dehname, wadname, "deh");
    fin = fopen (dehname, "r");
  }

  if (fin)
  {
    /* On a short name system, it's possible that I've just */
    /* opened the WAD file again, ensure that it's not! */

    dh_fgets (aline, 4, fin);

    if (dh_strcmp (aline,"PWAD") != 0)
    {
      if (do_it == true)
      {
	fseek (fin, 0, SEEK_SET);
	DH_parse_hacker_file_f (dehname, fin, ~0);
      }
      else
      {
	printf (" adding %s\n", dehname);
      }
    }
    fclose (fin);
  }
}

/* ---------------------------------------------------------------------------- */

static char * next_line (char * ptr, char * top)
{
  char cc;

  do
  {
    if (ptr >= top)
      return (ptr);
    cc = *ptr++;
  } while ((cc == '\t') || (cc >= ' '));

  while (*ptr < ' ')
  {
    if (ptr >= top)
      return (ptr);
    ptr++;
  }

  return (ptr);
}

/* ---------------------------------------------------------------------------- */

static char * split_lines (char * ptr, char * top)
{
  char cc;
  char * ptr_2;
  char * ptr_3;
  unsigned int quote;

  /* First look for lines that end in a ....", with the following starting with a quote */

  ptr_2 = ptr;
  do
  {
    if ((ptr_2 [0] == '\"')
     && (ptr_2 [1] == ',')
     && (ptr_2 [2] <= ' '))
    {
      ptr_3 = ptr_2 + 2;
      do
      {
	ptr_3++;
      } while ((*ptr_3 < ' ') && (ptr_3 < top));
      if (ptr_3 < top)
      {
	while (*ptr_3 == ' ')
	  ptr_3++;
	if (*ptr_3++ == '\"')
	{
	  *ptr_2++ = '\n';
	  memcpy (ptr_2, ptr_3, top - ptr_3);
	  top = top - (ptr_3 - ptr_2);
	  ptr_2--;
	}
      }
    }
  } while (++ptr_2 < top);

  quote = 0;
  do
  {
    cc = *ptr;
    if (cc == '\"')
    {
      quote = 1 - quote;
    }
    else
    {
      if ((cc < ' ')
       && (cc != '\t')
       && (quote == 0))
	*ptr = 0;
    }
  } while (++ptr < top);

  return (top);
}

/* ---------------------------------------------------------------------------- */

static char * read_map_num (unsigned int * episode, unsigned int * map, char * ptr)
{
  *map = 0;
  *episode = 255;

  do
  {
    switch (ptr [0])
    {
      case 'e':
      case 'E':
	*episode = ptr [1] - '0';
	*map = ptr [3] - '0';
	while (*ptr > ' ')
	  ptr++;
	return (ptr);

      case 'm':
      case 'M':
	if (((ptr[1] == 'a') || (ptr[1] == 'A'))
	 && ((ptr [2] == 'p') || (ptr[2] == 'P')))
	  *map = atoi (ptr+3);
	while (*ptr > ' ')
	  ptr++;
	return (ptr);
    }
    ptr++;
  } while (*ptr >= ' ');
  return (ptr);
}

/* ---------------------------------------------------------------------------- */

static unsigned int read_int (char * ptr)
{
  char cc;

  while (((cc = *ptr) != 0) && ((cc < '0') || (cc > '9')))
    ptr++;

  return (atoi (ptr));
}

/* ---------------------------------------------------------------------------- */

static void EV_DoNothing (void)
{
}

/* ---------------------------------------------------------------------------- */

static bossdeath_t * access_boss_actions (unsigned int episode, unsigned int map, bossdeath_t * bd_ptr)
{
  if (bd_ptr == NULL)
  {
    bd_ptr = malloc (sizeof (bossdeath_t) * 50);
    if (bd_ptr == NULL)
      return (bd_ptr);

    boss_death_table_2 = bd_ptr;
    memset (bd_ptr,0,sizeof (bossdeath_t) * 50);
  }

  if (bd_ptr -> func == NULL)
  {
    bd_ptr -> func = (actionf2) EV_DoNothing;
    bd_ptr -> tag = 666;
    bd_ptr -> episode = episode;
    bd_ptr -> map = map;
  }

  return (bd_ptr);
}

/* ---------------------------------------------------------------------------- */

static bossdeath_t * set_boss_action (bossdeath_t * bd_ptr, actionf2 func, unsigned int action)
{
  if (bd_ptr -> func != (actionf2) EV_DoNothing)	// This one already used?
  {
    memcpy (bd_ptr + 1, bd_ptr, sizeof (bossdeath_t));	// Yes. Make another
    bd_ptr++;
  }

  bd_ptr -> func = func;
  bd_ptr -> action = action;
  return (bd_ptr);
}

/* ---------------------------------------------------------------------------- */

static void show_boss_action (unsigned int bossnum, bossdeath_t * bd_ptr)
{
  char monsters [100];
  char * ptr;

  do
  {
    ptr = monsters;
    *ptr = 0;

    if (bd_ptr -> monsterbits & (1<<MT_FATSO))
      ptr += sprintf (ptr, " FATSO");
    if (bd_ptr -> monsterbits & (1<<MT_BABY))
      ptr += sprintf (ptr, " BABY");
    if (bd_ptr -> monsterbits & (1<<MT_BRUISER))
      ptr += sprintf (ptr, " BRUISER");
    if (bd_ptr -> monsterbits & (1<<MT_CYBORG))
      ptr += sprintf (ptr, " CYBORG");
    if (bd_ptr -> monsterbits & (1<<MT_SPIDER))
      ptr += sprintf (ptr, " SPIDER");

    printf ("Boss %u %u,%u%s %u %Xl %u\n",
		bossnum,
		bd_ptr -> episode,
		bd_ptr -> map,
		monsters,
		bd_ptr -> tag,
		(pint)bd_ptr -> func,
		bd_ptr -> action);
    bd_ptr++;
  } while (bd_ptr -> func);
}

/* ---------------------------------------------------------------------------- */

static void show_map_dests (map_dests_t * map_ptr)
{
  char * sky;
  char * titlepatch;


  sky = map_ptr -> sky;
  if (sky == NULL)
    sky = "";

  titlepatch = map_ptr -> titlepatch;
  if (titlepatch == NULL)
    titlepatch = "";

  printf ("%u %2u %u %2u %u %u %u %2u %u %3u '%s' '%s' '%s' '%s' '%s' '%s'\n",
	map_ptr -> normal_exit_to_episode,
	map_ptr -> normal_exit_to_map,
	map_ptr -> secret_exit_to_episode,
	map_ptr -> secret_exit_to_map,
	map_ptr -> this_is_a_secret_level,
	map_ptr -> reset_kit_etc_on_entering,
	map_ptr -> intermission_text,
	map_ptr -> cluster,
	map_ptr -> allow_monster_telefrags,
	map_ptr -> par_time_5 * 5,			// Par time divided by 5
	map_ptr -> mapname,
	sky, titlepatch,
	map_ptr -> enterpic,
	map_ptr -> exitpic,
	map_ptr -> bordertexture);
}

/* ---------------------------------------------------------------------------- */
/* Currently I'm not sure whether the boss death table replaces the original */
/* or supplements it. For now remove any duplicates. */

void DH_remove_duplicate_mapinfos (void)
{
  unsigned int i;
  unsigned int intertext;
  bossdeath_t * bd_ptr;
  bossdeath_t * bd_ptr_1;
  map_dests_t * map_ptr;

  if (boss_death_table_2)
  {
    bd_ptr = boss_death_table_2;
    do
    {
      bd_ptr_1 = boss_death_table;
      do
      {
	if ((bd_ptr_1 -> episode == bd_ptr -> episode)
	 && (bd_ptr_1 -> map == bd_ptr -> map)
	 && (bd_ptr_1 -> monsterbits & bd_ptr -> monsterbits)
	 && (bd_ptr_1 -> tag == bd_ptr -> tag)
	 && (bd_ptr_1 -> func == bd_ptr -> func)
	 && (bd_ptr_1 -> action == bd_ptr -> action))
	{
	  bd_ptr_1 -> monsterbits &= ~bd_ptr -> monsterbits;
//	  bd_ptr_1 -> tag = 0;		// and this inhibits the -nomonster cheat in A_Activate_Death_Sectors
//	  bd_ptr_1 -> func = (actionf2) EV_DoNothing;	// For safety!
//	  printf ("Removed duplicate boss action from %u,%u (%X %X)\n", bd_ptr_1 -> episode, bd_ptr_1 -> map, bd_ptr_1 -> monsterbits,bd_ptr -> monsterbits);
	}
	bd_ptr_1++;
      } while (bd_ptr_1 -> func);

      bd_ptr_1 = boss_death_table_2;
      do
      {
	if ((bd_ptr_1 != bd_ptr)
	 && (bd_ptr_1 -> episode == bd_ptr -> episode)
	 && (bd_ptr_1 -> map == bd_ptr -> map)
	 && (bd_ptr_1 -> monsterbits & bd_ptr -> monsterbits)
	 && (bd_ptr_1 -> tag == bd_ptr -> tag)
	 && (bd_ptr_1 -> func == bd_ptr -> func)
	 && (bd_ptr_1 -> action == bd_ptr -> action))
	{
	  bd_ptr_1 -> monsterbits &= ~bd_ptr -> monsterbits;
//	  bd_ptr_1 -> tag = 0;		// and this inhibits the -nomonster cheat in A_Activate_Death_Sectors
//	  bd_ptr_1 -> func = (actionf2) EV_DoNothing;	// For safety!
//	  printf ("Removed duplicate boss action from %u,%u (%X %X)\n", bd_ptr_1 -> episode, bd_ptr_1 -> map, bd_ptr_1 -> monsterbits,bd_ptr -> monsterbits);
	}
	bd_ptr_1++;
      } while (bd_ptr_1 -> func);

      bd_ptr++;
    } while (bd_ptr -> func);
  }

  if (M_CheckParm ("-showmonstertables"))
  {
    putchar ('\n');
    show_boss_action (1, boss_death_table);
    if ((bd_ptr = boss_death_table_2) != NULL)
      show_boss_action (2, bd_ptr);

    if (finale_clusterdefs)
    {
      intertext = 0;
      do
      {
	if ((pint)finale_clusterdefs[intertext].flat
	 | (pint)finale_clusterdefs[intertext].entertext
	 | (pint)finale_clusterdefs[intertext].exittext)
	{
	  printf ("Clusterdefs %u\n", intertext);
	  if (finale_clusterdefs[intertext].flat == 0)
	    printf ("flat = NULL\n");
	  else
	    printf ("flat = %s\n", finale_clusterdefs[intertext].flat);
	  if (finale_clusterdefs[intertext].entertext == 0)
	    printf ("Enter = NULL\n");
	  else
	    printf ("Enter = %s\n", finale_clusterdefs[intertext].entertext);
	  if (finale_clusterdefs[intertext].exittext == 0)
	    printf ("Exit = NULL\n");
	  else
	    printf ("Exit = %s\n", finale_clusterdefs[intertext].exittext);
	}
      } while (++intertext < QTY_CLUSTERDEFS);
    }
  }
  if (M_CheckParm ("-showmaptables"))
  {
    putchar ('\n');

    i = (9*10);
    map_ptr = G_Access_MapInfoTab_E (1,0);
    do
    {
      show_map_dests (map_ptr);
      map_ptr++;
    } while (--i);

    i = 100;
    map_ptr = G_Access_MapInfoTab_E (255,0);
    do
    {
      show_map_dests (map_ptr);
      map_ptr++;
    } while (--i);
  }
}

/* ---------------------------------------------------------------------------- */

static char * set_enter_exit_text (char * ptr, unsigned int doexit, unsigned int intertext, unsigned int episode, unsigned int map)
{
  char cc;
  unsigned int l;
  int lump;
  unsigned int length;
  char * newtext;
  char * lump_ptr;
  char ** source;
  //bossdeath_t * bd_ptr;
  map_dests_t * mdest_ptr;

  // printf ("set_enter_exit_text (%s), %u, %u, %u\n", ptr, intertext, episode, map);

  do
  {
    cc = *ptr;
    if ((cc != ' ') && (cc != '=') && (cc != ','))
      break;
    ptr++;
  } while (*ptr);

  if (*ptr == '\"')
    ptr++;

  l = dh_inchar (ptr, '"');
  if (l) ptr[l-1] = 0;

  newtext = NULL;

  // printf ("Looking for text lump %s\n", ptr);
  lump = W_CheckNumForName (ptr);
  if (lump == -1)
  {
    source = DH_Find_language_text (ptr, false);
    if (source)
      newtext = *source;
  }
  else
  {
    length = W_LumpLength (lump);
    if (length)
    {
      // printf ("Lump is %u bytes\n", length);
      lump_ptr = W_CacheLumpNum (lump, PU_STATIC);
      // length = split_lines (lump_ptr, lump_ptr + length) - lump_ptr;
      newtext = malloc (length + 20);
      if (newtext)
      {
	strncpy (newtext, lump_ptr, length);
	newtext [length] = 0;
	dh_remove_americanisms (newtext);
      }
      Z_Free (lump_ptr);
    }
  }

  if (newtext == NULL)
  {
    if (M_CheckParm ("-showunknown"))
      fprintf (stderr,"DeHackEd:Failed to lookup text %s\n", ptr);
  }
  else
  {
    if (finale_clusterdefs == 0)
    {
      finale_clusterdefs = malloc (sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
      if (finale_clusterdefs)
	memset (finale_clusterdefs,0,sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
    }

    if ((finale_clusterdefs) && (intertext < QTY_CLUSTERDEFS))
    {
      if ((episode != 255) && (map != 255))
      {
	mdest_ptr = G_Access_MapInfoTab_E (episode, map);
	/* Fix for DTWID-LE */
	if (mdest_ptr -> cluster == 0)
	  mdest_ptr -> cluster = intertext;
      }
      if (doexit)
	finale_clusterdefs[intertext].exittext = newtext;
      else
	finale_clusterdefs[intertext].entertext = newtext;
      finale_message_changed = (boolean)((int)finale_message_changed|(int)dh_changing_pwad);
      // printf ("Exit Text %u (%s) = %s\n", intertext, ptr, newtext);
    }
  }

  return (ptr);
}

/* ---------------------------------------------------------------------------- */

static void replace_map_name (const char * ptr, unsigned int episode, unsigned int map)
{
  char cc;
  unsigned int pos;
  map_dests_t * mdest_ptr;
  char * newname;
  char buf1 [12];
  char buf2 [12];

  pos = 0;
  do
  {
    cc = *ptr++;
    if (cc <= ' ') cc = 0;
    buf1 [pos++] = cc;
  } while (cc);

  G_MapName (buf2, episode, map);

  if (strcasecmp (buf1, buf2))
  {
    newname = strdup (buf1);
    if (newname)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> mapname = newname;
      // printf ("Mapname changed to %s\n", newname);
    }
  }
}

/* ---------------------------------------------------------------------------- */

static char * replace_titletext (char * ptr, unsigned int episode, unsigned int map)
{
  unsigned int j;
  char * newtext;
  map_dests_t * mdest_ptr;
  char buf [12];

  if (*ptr == '=') ptr++;
  while (*ptr == ' ') ptr++;
  if (*ptr == '\"') ptr++;
  j = dh_inchar (ptr, ' ');
  if (j) ptr [j-1] = 0;
  j = dh_inchar (ptr, '"');
  if (j) ptr [j-1] = 0;

  mdest_ptr = G_Access_MapInfoTab_E (episode, map);

  buf [0] = 0;

  if (episode == 255)
  {
    if (map) sprintf (buf, mdest_ptr -> titlepatch, map-1);
  }
  else
  {
    if (episode && map) sprintf (buf, mdest_ptr -> titlepatch, episode-1, map-1);
  }

  if (strcasecmp (ptr, buf))
  {
    newtext = strdup (ptr);
    if (newtext)
    {
      mdest_ptr -> titlepatch = newtext;
      // printf ("titlepatch %u,%u = '%s'\n", episode, map, mdest_ptr -> titlepatch);
    }
  }

  return (ptr);
}

/* ---------------------------------------------------------------------------- */

static char * replace_map_text (char ** dest, char * ptr)
{
  unsigned int j;
  char * newtext;

  if (*ptr == '=') ptr++;
  while (*ptr == ' ') ptr++;
  if (*ptr == '\"') ptr++;
  j = dh_inchar (ptr, ' ');
  if (j) ptr [j-1] = 0;
  j = dh_inchar (ptr, '"');
  if (j) ptr [j-1] = 0;

  if (strcasecmp (ptr, *dest))
  {
    newtext = strdup (ptr);
    if (newtext)
    {
      *dest = newtext;
      // printf ("map text = '%s'\n", ptr);
    }
  }

  return (ptr);
}

/* ---------------------------------------------------------------------------- */

void Parse_Mapinfo (char * ptr, char * top)
{
  char cc;
  unsigned int i,j,l;
  unsigned int episode;
  unsigned int map;
  unsigned int intertext;
  unsigned int doing_episode;
  char * ptr2;
  char * newtext;
  bossdeath_t * bd_ptr;
  map_dests_t * mdest_ptr;

  top = split_lines (ptr, top);

  episode = 9;
  map = 9;
  intertext = 1;
  bd_ptr = boss_death_table_2;

  if (bd_ptr)
  {
    while (bd_ptr -> func != NULL)
      bd_ptr++;
  }

  do
  {
    while (((cc = *ptr) <= ' ') || (cc == '{')) ptr++;
    if (strncasecmp (ptr, "episode ", 8) == 0)
    {
      ptr = read_map_num (&episode, &map, ptr+8);
      doing_episode = 1;
      intertext = 0;
    }
    else if (strncasecmp (ptr, "name ", 5) == 0)
    {
      /* Note: Nerve.wad gets to here but episode == 255 */
      if ((doing_episode) && (episode < 10)
       && (dh_instr (ptr, "HUSTR_E") == 0))
      {
	ptr += 5;
	while ((*ptr == ' ') || (*ptr == '=')) ptr++;
	if (*ptr == '\"')
	{
	  ptr++;
	  l = dh_inchar (ptr , '"');
	  if (l)
	    l--;
	  else
	    l = strlen (ptr);
	}
	else
	{
	  l = strlen (ptr);
	}
	newtext = malloc (l+6);
	if (newtext)
	{
	  strncpy (newtext, ptr, l);
	  newtext [l] = 0;
	  dh_remove_americanisms (newtext);
	  episode_names [episode] = newtext;
	  // printf ("Episode %u name is \'%s\'\n", episode, newtext);
	}
      }
    }
    else if (strncasecmp (ptr, "key ", 4) == 0)
    {
      if ((doing_episode) && (episode < 10))
      {
	l = dh_inchar (ptr , '"');
	if (l)
	{
	  M_SetEpiKey (episode, ptr [l]);
	  // printf ("Set menu key for episode %u to %c\n", episode, ptr [l]);
	}
      }
    }
    else if (strncasecmp (ptr, "map ", 4) == 0)
    {
      doing_episode = 0;
      intertext = 0;
      ptr2 = read_map_num (&episode, &map, ptr+4);
      replace_map_name (ptr+4, episode, map);
      ptr = ptr2;
      i = dh_inchar (ptr, '"');
      if ((i) && (dh_instr (ptr, "lookup \"HUSTR") == 0))
      {
	l = dh_inchar (ptr + i, '"');
	if (l)
	{
	  if (episode != 255)
	  {
	    newtext = malloc (l+16);	// +6 for the "ExMx: " and +10 for the american/british conv
	    if (newtext)
	    {
	      j = sprintf (newtext, "E%dM%d: ", episode, map);
	      strncpy (newtext+j, ptr+i, l);
	      newtext [l+j-1] = 0;
	      dh_remove_americanisms (newtext);
	      *(HU_access_mapname_E (episode,map)) = newtext;
	      mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
	    }
	  }
	  else
	  {
	    newtext = malloc (l+20);
	    if (newtext)
	    {
	      sprintf (newtext, " %d:", map);			// Do not prepend "Level xx:" if there appears
	      if (dh_instr (ptr+i, newtext))			// to be an xx: already there.
		j = 0;
	      else
		j = sprintf (newtext, "Level %d: ", map);
	      strncpy (newtext+j, ptr+i, l);
	      newtext [l+j-1] = 0;
	      dh_remove_americanisms (newtext);
	      *(HU_access_mapname_E (255,map)) = newtext;
	      *(HU_access_mapname_E (254,map)) = newtext;	// Do TNT and Plutonia as well for completeness...
	      *(HU_access_mapname_E (253,map)) = newtext;
	      mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
	    }
	  }
	  //printf ("Map %u %u has %u text (%s)\n", episode, map, l, newtext);
	}
      }
      if ((bd_ptr) && (bd_ptr -> func)) bd_ptr++;
    }
    else if (strncasecmp (ptr, "next ", 5) == 0)
    {
      ptr += 5;
      j = dh_inchar (ptr, '='); if (j) ptr += j;
      j = dh_inchar (ptr, '"'); if (j) ptr += j;
      if (strncasecmp (ptr, "End", 3) == 0)
      {
	j = 255;
	i = 255;
      }
      else
      {
	read_map_num (&i, &j, ptr);
      }
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> normal_exit_to_episode = i;
      mdest_ptr -> normal_exit_to_map = j;
      // printf ("Map %u %u has exit to %u %u\n", episode, map, i, j);
    }
    else if (strncasecmp (ptr, "secretnext ", 11) == 0)
    {
      ptr += 11;
      j = dh_inchar (ptr, '='); if (j) ptr += j;
      j = dh_inchar (ptr, '"'); if (j) ptr += j;
      if (strncasecmp (ptr, "End", 3) == 0)
      {
	i = 255;
	j = 255;
      }
      else
      {
	read_map_num (&i, &j, ptr);
      }
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> secret_exit_to_episode = i;
      mdest_ptr -> secret_exit_to_map = j;
      // printf ("Map %u %u has secret exit to %u %u\n", episode, map, i, j);
#if 0
      /* While we are here, mark the destination map as a secret. */
      /* Nope, we cannot, WOS level 99 is a hub with two exits,   */
      /* the 'secret' one goes to map 27. */
      if (j != 255)
      {
	mdest_ptr = G_Access_MapInfoTab_E (i, j);
	mdest_ptr -> this_is_a_secret_level = 0x80;
      }
#endif
    }
    else if (strncasecmp (ptr, "nointermission", 14) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> nointermission = 1;
    }
    else if (strncasecmp (ptr, "cluster ", 8) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      /* We set the intertext variable here because DTWID-LE uses */
      /* "cluster" instead of "clusterdef". */
      /* We avoid corrupting the "mdest_ptr -> cluster" later in */
      /* the function "set_enter_exit_text" by ensuring that it is */
      /* zero first in that function. */
      intertext = read_int (ptr+8);
      mdest_ptr -> cluster = intertext;
      //printf ("Map %u %u is in cluster %u\n", episode, map, mdest_ptr -> cluster);
    }
    else if (strncasecmp (ptr, "par ", 4) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      l = read_int (ptr+4);
      l = (l+4)/5;
      if (l > 255) l = 255;
      mdest_ptr -> par_time_5 = l;
      par_changed = (boolean)((int)par_changed|(int)dh_changing_pwad);
      // printf ("Map %u %u par time %u\n", episode, map, l);
    }
    else if (strncasecmp (ptr, "sucktime ", 9) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      l = read_int (ptr+9);
      if (l > 255) l = 255;
      mdest_ptr -> time_sucks = l;
      // printf ("Map %u %u sucks time %u\n", episode, map, l);
    }
    else if (strncasecmp (ptr, "resethealth", 11) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> reset_kit_etc_on_entering = 1;
    }
    else if (strncasecmp (ptr, "resetinventory", 14) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> reset_kit_etc_on_entering = 1;
    }
    else if (strncasecmp (ptr, "allowmonstertelefrags", 21) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      mdest_ptr -> allow_monster_telefrags = 1;
    }
    else if (strncasecmp (ptr, "NoInfighting", 12) == 0)
    {
    }
    else if (strncasecmp (ptr, "NormalInfighting", 16) == 0)
    {
    }
    else if (strncasecmp (ptr, "TotalInfighting", 15) == 0)
    {
    }
    else if (strncasecmp (ptr, "titlepatch", 10) == 0)
    {
      ptr = replace_titletext (ptr+11, episode, map);
    }
    else if (strncasecmp (ptr, "enterpic ", 9) == 0)
    {
      /* Picture used as the backdrop for the 'entering level' screen. */
      /* If starts with a $ then the lump is an 'intermission script' */
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      ptr = replace_map_text (&mdest_ptr -> enterpic, ptr+10);
    }
    else if (strncasecmp (ptr, "exitpic ", 8) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      ptr = replace_map_text (&mdest_ptr -> exitpic, ptr+9);
    }
    else if (strncasecmp (ptr, "bordertexture ", 14) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      ptr = replace_map_text (&mdest_ptr -> bordertexture, ptr + 15);
    }
    else if (strncasecmp (ptr, "sky1 ", 5) == 0)
    {
      mdest_ptr = G_Access_MapInfoTab_E (episode, map);
      ptr = replace_map_text (&mdest_ptr -> sky, ptr + 5);
    }
    else if (strncasecmp (ptr, "map07special", 12) == 0)
    {
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
      {
	bd_ptr -> monsterbits = 1<<MT_FATSO;
	bd_ptr -> func = (actionf2) EV_DoFloor;
	bd_ptr -> action = lowerFloorToLowest;
	bd_ptr++;
	bd_ptr -> episode = episode;
	bd_ptr -> map = map;
	bd_ptr -> tag = 667;
	bd_ptr -> monsterbits = 1<<MT_BABY;
	bd_ptr -> func = (actionf2) EV_DoFloor;
	bd_ptr -> action = raiseToTexture;
      }
    }
    else if (strncasecmp (ptr, "baronspecial", 12) == 0)
    {
      //printf ("baronspecial\n");
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_BRUISER;
    }
    else if (strncasecmp (ptr, "cyberdemonspecial", 17) == 0)
    {
      //printf ("cyberdemonspecial\n");
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_CYBORG;
    }
    else if (strncasecmp (ptr, "spidermastermindspecial", 23) == 0)
    {
      //printf ("spidermastermindspecial\n");
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_SPIDER;
    }
#if 0
    else if (strncasecmp (ptr, "ironlichspecial", 15) == 0)
    {
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_???;
    }
    else if (strncasecmp (ptr, "minotaurspecial", 15) == 0)
    {
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_???;
    }
    else if (strncasecmp (ptr, "dsparilspecial", 14) == 0)
    {
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
	bd_ptr -> monsterbits |= 1<<MT_???;
    }
#endif
    else if (strncasecmp (ptr, "specialaction_", 14) == 0)
    {
      ptr += 14;
      bd_ptr = access_boss_actions (episode, map, bd_ptr);
      if (bd_ptr)
      {
	if (strncasecmp (ptr, "lowerfloor", 10) == 0)
	{
	  bd_ptr = set_boss_action (bd_ptr, (actionf2) EV_DoFloor, lowerFloorToLowest);
	}
	if (strncasecmp (ptr, "opendoor", 8) == 0)
	{
	  bd_ptr = set_boss_action (bd_ptr, (actionf2) EV_DoDoor, blazeOpen);
	}
	else if (strncasecmp (ptr, "exitlevel", 9) == 0)
	{
	  bd_ptr -> func = (actionf2) G_ExitLevel;
	  bd_ptr -> tag = 0;
	}
	else if (strncasecmp (ptr, "killmonsters", 12) == 0)
	{
	  bd_ptr = set_boss_action (bd_ptr, (actionf2) P_Massacre, 0);
	  bd_ptr -> tag = 0;
	}
	else if (strncasecmp (ptr, "tag", 3) == 0)
	{
	  bd_ptr -> tag = read_int (ptr);
	}
      }
    }
    else if (strncasecmp (ptr, "clusterdef ", 11) == 0)
    {
      intertext = read_int (ptr + 11);
      episode = 255;
      map = 255;
    }
    else if (strncasecmp (ptr, "entertext", 9) == 0)
    {
      i = dh_inchar (ptr, '"');
      j = dh_instr (ptr, "lookup");
      if ((j) && (j < i))
      {
	ptr = set_enter_exit_text (ptr+j+5, 0, intertext, episode, map);
      }
      else if (i && (ptr[i] == '$'))
      {
	ptr = set_enter_exit_text (ptr+i+1, 0, intertext, episode, map);
      }
      else
      {
	if (i == 0)
	{
	  ptr = next_line (ptr,top);
	  i = dh_inchar (ptr, '"');
	}
	if (i)
	{
	  l = dh_inchar (ptr + i, '"');
	  if (l)
	  {
	    newtext = malloc (l+10);
	    if (newtext)
	    {
	      l--;
	      strncpy (newtext, ptr+i, l);
	      newtext [l] = 0;
	      ptr += l;
	      dh_remove_americanisms (newtext);
	      if (finale_clusterdefs == 0)
	      {
		finale_clusterdefs = malloc (sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
		if (finale_clusterdefs)
		  memset (finale_clusterdefs,0,sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	      }
	      if ((finale_clusterdefs) && (intertext < QTY_CLUSTERDEFS))
	      {
		finale_clusterdefs[intertext].entertext = newtext;
		finale_message_changed = (boolean)((int)finale_message_changed|(int)dh_changing_pwad);
		// printf ("Enter Text %u = %s\n", intertext, newtext);
	      }
	    }
	  }
	}
      }
    }
    else if (strncasecmp (ptr, "exittext", 8) == 0)
    {
      i = dh_inchar (ptr, '"');
      j = dh_instr (ptr, "lookup");
      if ((j) && (j < i))
      {
	ptr = set_enter_exit_text (ptr+j+5, 1, intertext, episode, map);
      }
      else if (i && (ptr[i] == '$'))
      {
	ptr = set_enter_exit_text (ptr+i+1, 1, intertext, episode, map);
      }
      else
      {
	if (i == 0)
	{
	  ptr = next_line (ptr,top);
	  i = dh_inchar (ptr, '"');
	}
	if (i)
	{
	  l = dh_inchar (ptr + i, '"');
	  if (l)
	  {
	    newtext = malloc (l+10);
	    if (newtext)
	    {
	      l--;
	      strncpy (newtext, ptr+i, l);
	      ptr += l;
	      newtext [l] = 0;
	      dh_remove_americanisms (newtext);
	      if (finale_clusterdefs == 0)
	      {
		finale_clusterdefs = malloc (sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
		if (finale_clusterdefs)
		  memset (finale_clusterdefs,0,sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	      }
	      if ((finale_clusterdefs) && (intertext < QTY_CLUSTERDEFS))
	      {
		finale_clusterdefs[intertext].exittext = newtext;
		finale_message_changed = (boolean)((int)finale_message_changed|(int)dh_changing_pwad);
		// printf ("Exit Text %u = %s\n", intertext, newtext);
	      }
	    }
	  }
	}
      }
    }
    else if (strncasecmp (ptr, "flat ", 5) == 0)
    {
      ptr += 5;
      if (*ptr == '=') ptr++;
      while (*ptr == ' ') ptr++;
      if (*ptr == '\"') ptr++;
      j = dh_inchar (ptr, ' ');
      if (j) ptr [j-1] = 0;
      j = dh_inchar (ptr, '"');
      if (j) ptr [j-1] = 0;
      l = strlen (ptr);
      newtext = malloc (l+1);
      if (newtext)
      {
	strcpy (newtext, ptr);
	if (finale_clusterdefs == 0)
	{
	  finale_clusterdefs = malloc (sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	  if (finale_clusterdefs)
	    memset (finale_clusterdefs,0,sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	}
	if ((finale_clusterdefs) && (intertext < QTY_CLUSTERDEFS))
	{
	  finale_clusterdefs[intertext].flat = newtext;
	  // printf ("Cluster flat %u = \'%s\'\n", intertext, newtext);
	}
      }
    }
    ptr = next_line (ptr,top);
  } while (ptr < top);
}

/* ---------------------------------------------------------------------------- */

void Parse_IndivMapinfo (char * ptr, char * top, unsigned int episode, unsigned int map)
{
  char cc;
  unsigned int i,j,l;
  unsigned int intertext;
  char * newtext;
  //bossdeath_t * bd_ptr;
  map_dests_t * mdest_ptr;

  top = split_lines (ptr, top);

#if 0
  bd_ptr = boss_death_table_2;

  if (bd_ptr)
  {
    while (bd_ptr -> func != NULL)
      bd_ptr++;
  }
#endif

  mdest_ptr = G_Access_MapInfoTab_E (episode, map);

  do
  {
    while (((cc = *ptr) <= ' ') || (cc == '{')) ptr++;

    if (strncasecmp (ptr, "levelname", 9) == 0)
    {
      ptr += 9;
      while (*ptr == ' ') ptr++;
      while (*ptr == '=') ptr++;
      while (*ptr == ' ') ptr++;
      if (*ptr == '\"')
      {
	ptr++;
	l = dh_inchar (ptr, '"');
	if (l) ptr[l-1] = 0;
      }
      l = strlen (ptr);
      if (episode != 255)
      {
	newtext = malloc (l+16);	// +6 for the "ExMx: " and +10 for the american/british conv
	if (newtext)
	{
	  j = sprintf (newtext, "E%dM%d: ", episode, map);
	  strncpy (newtext+j, ptr, l);
	  newtext [l+j] = 0;
	  dh_remove_americanisms (newtext);
	  *(HU_access_mapname_E (episode,map)) = newtext;
	  mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
	}
      }
      else
      {
	newtext = malloc (l+20);
	if (newtext)
	{
	  sprintf (newtext, " %d:", map);			// Do not prepend "Level xx:" if there appears
	  if (dh_instr (ptr, newtext))				// to be an xx: already there.
	    j = 0;
	  else
	    j = sprintf (newtext, "Level %d: ", map);
	  strncpy (newtext+j, ptr, l);
	  newtext [l+j] = 0;
	  dh_remove_americanisms (newtext);
	  *(HU_access_mapname_E (255,map)) = newtext;
	  *(HU_access_mapname_E (254,map)) = newtext;	// Do TNT and Plutonia as well for completeness...
	  *(HU_access_mapname_E (253,map)) = newtext;
	  mapnameschanged = (boolean)((int)mapnameschanged|(int)dh_changing_pwad);
	  // printf ("Mapname %u changed to %s\n", map, newtext);
	}
      }
    }
    else if (strncasecmp (ptr, "nextlevel", 9) == 0)
    {
      while (((cc = *ptr) < '0') || (cc > '9')) ptr++;
      if (episode == 255)
      {
	j = atoi (ptr);
	mdest_ptr -> normal_exit_to_map = j;
      }
      else
      {
	i = ptr [0] - '0';
	j = ptr [2] - '0';
	mdest_ptr -> normal_exit_to_episode = i;
	mdest_ptr -> normal_exit_to_map = j;
      }
      //printf ("Map %u %u has exit to %u %u\n", episode, map, i, j);
    }
    else if (strncasecmp (ptr, "nextsecret", 10) == 0)
    {
      while (((cc = *ptr) < '0') || (cc > '9')) ptr++;
      if (episode == 255)
      {
	j = atoi (ptr);
	mdest_ptr -> secret_exit_to_map = j;
      }
      else
      {
	i = ptr [0] - '0';
	j = ptr [2] - '0';
	mdest_ptr -> secret_exit_to_episode = i;
	mdest_ptr -> secret_exit_to_map = j;
      }
    }
    else if (strncasecmp (ptr, "endofgame = true", 16) == 0)
    {
      mdest_ptr -> normal_exit_to_map = 255;
      mdest_ptr -> normal_exit_to_episode = 255;
    }
    else if (strncasecmp (ptr, "intertext", 9) == 0)
    {
      if (episode == 255)
	intertext = map;
      else
	intertext = (episode*10)+map;

      ptr = set_enter_exit_text (ptr+9, 1, intertext, episode, map);
    }
    else if (strncasecmp (ptr, "inter-backdrop", 14) == 0)
    {
      ptr += 14;
      while (*ptr == ' ') ptr++;
      while (*ptr == '=') ptr++;
      while (*ptr == ' ') ptr++;
      if (*ptr == '\"')
      {
	ptr++;
	l = dh_inchar (ptr, '"');
	if (l) ptr[l-1] = 0;
      }
      l = strlen (ptr);
      newtext = malloc (l+1);
      if (newtext)
      {
	strcpy (newtext, ptr);
	if (finale_clusterdefs == 0)
	{
	  finale_clusterdefs = malloc (sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	  if (finale_clusterdefs)
	    memset (finale_clusterdefs,0,sizeof (clusterdefs_t) * QTY_CLUSTERDEFS);
	}

	if (episode == 255)
	  intertext = map;
	else
	  intertext = (episode*10)+map;

	if ((finale_clusterdefs) && (intertext < QTY_CLUSTERDEFS))
	{
	  mdest_ptr -> cluster = intertext;
	  finale_clusterdefs[intertext].flat = newtext;
	  //printf ("Cluster flat %u = \'%s\'\n", intertext, newtext);
	}
      }
    }
    else if (strncasecmp (ptr, "killfinale = true", 17) == 0)
    {
      mdest_ptr -> intermission_text = 0;
    }
    else
    {
      // printf ("Parsing %s\n", ptr);
    }

    ptr = next_line (ptr,top);
  } while (ptr < top);
}

/* ---------------------------------------------------------------------------- */

void Load_Mapinfo (void)
{
  int lump;
  unsigned int episode;
  unsigned int map;
  unsigned int length;
  char * ptr;
  char * top;
  map_dests_t * mptr;
  char mapname [12];

  // DTWID-LE requires both MAPINFO & ZMAPINFO, whereas D2TWID requires only one....

  lump = 0;
  do
  {
    if ((strncasecmp (lumpinfo[lump].name, "MAPINFO", 8) == 0)
     || (strncasecmp (lumpinfo[lump].name, "ZMAPINFO", 8) == 0))
    {
      dh_changing_pwad = (boolean) !W_SameWadfile (0, lump);
      ptr = W_CacheLumpNum (lump, PU_STATIC);
      top = ptr + W_LumpLength (lump);
      Parse_Mapinfo (ptr, top);
      Z_Free (ptr);
    }
  } while (++lump < numlumps);

  map = 0;
  do
  {
    mptr = G_Access_MapInfoTab_E (255, map);
    sprintf (mapname, mptr -> mapname, map);
    lump = W_CheckNumForName (mapname);
    if (lump != -1)
    {
      length = W_LumpLength (lump);
      if (length)
      {
	dh_changing_pwad = (boolean) !W_SameWadfile (0, lump);
	ptr = W_CacheLumpNum (lump, PU_STATIC);
	top = ptr + length;
	Parse_IndivMapinfo (ptr, top, 255, map);
	Z_Free (ptr);
      }
    }
  } while (++map < 100);

  episode = 0;
  do
  {
    map = 0;
    do
    {
      mptr = G_Access_MapInfoTab_E (episode, map);
      sprintf (mapname, mptr -> mapname, episode, map);
      lump = W_CheckNumForName (mapname);
      if (lump != -1)
      {
	length = W_LumpLength (lump);
	if (length)
	{
	  dh_changing_pwad = (boolean) !W_SameWadfile (0, lump);
	  ptr = W_CacheLumpNum (lump, PU_STATIC);
	  top = ptr + length;
	  Parse_IndivMapinfo (ptr, top, episode, map);
	  Z_Free (ptr);
	}
      }
    } while (++map < 10);
  } while (++episode < 10);

  // DH_DetectPwads ();
}

/* ---------------------------------------------------------------------------- */

void Change_To_Mapinfo (FILE * fin)
{
  long int pos;
  size_t size;
  char * ptr;

  pos = ftell (fin);
  fseek (fin, 0, SEEK_END);
  size = (size_t) (ftell (fin) - pos);
  fseek (fin, pos, SEEK_SET);

  ptr = malloc (size);
  if (ptr)
  {
    size = fread (ptr, 1, size, fin);
    Parse_Mapinfo (ptr, ptr+size);
    free (ptr);
  }
}

/* ---------------------------------------------------------------------------- */
