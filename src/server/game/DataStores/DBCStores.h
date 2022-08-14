/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIRELANDS_DBCSTORES_H
#define FIRELANDS_DBCSTORES_H

#include "DBCStore.h"
#include "DBCStructure.h"
#include "SharedDefines.h"
#include <list>
#include <map>
#include <unordered_map>

enum LocaleConstant : uint8;

// temporary hack until includes are sorted out (don't want to pull in Windows.h)
#ifdef GetClassName
#undef GetClassName
#endif

typedef std::list<uint32> SimpleFactionsList;
typedef std::map<uint32/*pair32(map, diff)*/, MapDifficulty> MapDifficultyMap;
typedef std::unordered_multimap<uint32, SkillRaceClassInfoEntry const*> SkillRaceClassInfoMap;
typedef std::pair<SkillRaceClassInfoMap::iterator, SkillRaceClassInfoMap::iterator> SkillRaceClassInfoBounds;

FC_GAME_API extern DBCStorage <AchievementEntry>             sAchievementStore;
FC_GAME_API extern DBCStorage <AnimKitEntry>                 sAnimKitStore;
FC_GAME_API extern DBCStorage <AchievementCriteriaEntry>     sAchievementCriteriaStore;
FC_GAME_API extern DBCStorage <AreaTableEntry>               sAreaTableStore;
FC_GAME_API extern DBCStorage <AreaGroupEntry>               sAreaGroupStore;
FC_GAME_API extern DBCStorage <AreaPOIEntry>                 sAreaPOIStore;
FC_GAME_API extern DBCStorage <AreaTriggerEntry>             sAreaTriggerStore;
FC_GAME_API extern DBCStorage <ArmorLocationEntry>           sArmorLocationStore;
FC_GAME_API extern DBCStorage <AuctionHouseEntry>            sAuctionHouseStore;
FC_GAME_API extern DBCStorage <BankBagSlotPricesEntry>       sBankBagSlotPricesStore;
FC_GAME_API extern DBCStorage <BannedAddOnsEntry>            sBannedAddOnsStore;
FC_GAME_API extern DBCStorage <BarberShopStyleEntry>         sBarberShopStyleStore;
FC_GAME_API extern DBCStorage <BattlemasterListEntry>        sBattlemasterListStore;
FC_GAME_API extern DBCStorage <ChatChannelsEntry>            sChatChannelsStore;
FC_GAME_API extern DBCStorage <CharStartOutfitEntry>         sCharStartOutfitStore;
FC_GAME_API extern DBCStorage <CharSectionsEntry>            sCharSectionsStore;
FC_GAME_API extern DBCStorage <CharTitlesEntry>              sCharTitlesStore;
FC_GAME_API extern DBCStorage <ChrClassesEntry>              sChrClassesStore;
FC_GAME_API extern DBCStorage <ChrRacesEntry>                sChrRacesStore;
FC_GAME_API extern DBCStorage <ChrPowerTypesEntry>           sChrPowerTypesStore;
FC_GAME_API extern DBCStorage <CinematicCameraEntry>         sCinematicCameraStore;
FC_GAME_API extern DBCStorage <CinematicSequencesEntry>      sCinematicSequencesStore;
FC_GAME_API extern DBCStorage <CreatureDisplayInfoEntry>     sCreatureDisplayInfoStore;
FC_GAME_API extern DBCStorage <CreatureDisplayInfoExtraEntry> sCreatureDisplayInfoExtraStore;
FC_GAME_API extern DBCStorage <CreatureFamilyEntry>          sCreatureFamilyStore;
FC_GAME_API extern DBCStorage <CreatureModelDataEntry>       sCreatureModelDataStore;
FC_GAME_API extern DBCStorage <CreatureSpellDataEntry>       sCreatureSpellDataStore;
FC_GAME_API extern DBCStorage <CreatureTypeEntry>            sCreatureTypeStore;
FC_GAME_API extern DBCStorage <CurrencyTypesEntry>           sCurrencyTypesStore;
FC_GAME_API extern DBCStorage <DestructibleModelDataEntry>   sDestructibleModelDataStore;
FC_GAME_API extern DBCStorage <DungeonEncounterEntry>        sDungeonEncounterStore;
FC_GAME_API extern DBCStorage <DurabilityCostsEntry>         sDurabilityCostsStore;
FC_GAME_API extern DBCStorage <DurabilityQualityEntry>       sDurabilityQualityStore;
FC_GAME_API extern DBCStorage <EmotesEntry>                  sEmotesStore;
FC_GAME_API extern DBCStorage <EmotesTextEntry>              sEmotesTextStore;
FC_GAME_API extern DBCStorage <EmotesTextSoundEntry>         sEmotesTextSoundStore;
FC_GAME_API extern DBCStorage <FactionEntry>                 sFactionStore;
FC_GAME_API extern DBCStorage <FactionTemplateEntry>         sFactionTemplateStore;
FC_GAME_API extern DBCStorage <GameObjectArtKitEntry>        sGameObjectArtKitStore;
FC_GAME_API extern DBCStorage <GameObjectDisplayInfoEntry>   sGameObjectDisplayInfoStore;
FC_GAME_API extern DBCStorage <GemPropertiesEntry>           sGemPropertiesStore;
FC_GAME_API extern DBCStorage <GlyphPropertiesEntry>         sGlyphPropertiesStore;
FC_GAME_API extern DBCStorage <GlyphSlotEntry>               sGlyphSlotStore;

FC_GAME_API extern DBCStorage <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore;
FC_GAME_API extern DBCStorage <GtCombatRatingsEntry>         sGtCombatRatingsStore;
FC_GAME_API extern DBCStorage <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore;
FC_GAME_API extern DBCStorage <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore;
FC_GAME_API extern DBCStorage <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore;
FC_GAME_API extern DBCStorage <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore;
FC_GAME_API extern DBCStorage <GtNPCManaCostScalerEntry>     sGtNPCManaCostScalerStore;
FC_GAME_API extern DBCStorage <GtOCTClassCombatRatingScalarEntry> sGtOCTClassCombatRatingScalarStore;
//FC_GAME_API extern DBCStorage <GtOCTRegenMPEntry>            sGtOCTRegenMPStore; -- not used currently
FC_GAME_API extern DBCStorage <gtOCTHpPerStaminaEntry>       sGtOCTHpPerStaminaStore;
FC_GAME_API extern DBCStorage <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore;
FC_GAME_API extern DBCStorage <GtSpellScalingEntry>          sGtSpellScalingStore;
FC_GAME_API extern DBCStorage <GtOCTBaseHPByClassEntry>      sGtOCTBaseHPByClassStore;
FC_GAME_API extern DBCStorage <GtOCTBaseMPByClassEntry>      sGtOCTBaseMPByClassStore;
FC_GAME_API extern DBCStorage <GuildPerkSpellsEntry>         sGuildPerkSpellsStore;
FC_GAME_API extern DBCStorage <HolidaysEntry>                sHolidaysStore;
FC_GAME_API extern DBCStorage <ImportPriceArmorEntry>        sImportPriceArmorStore;
FC_GAME_API extern DBCStorage <ImportPriceQualityEntry>      sImportPriceQualityStore;
FC_GAME_API extern DBCStorage <ImportPriceShieldEntry>       sImportPriceShieldStore;
FC_GAME_API extern DBCStorage <ImportPriceWeaponEntry>       sImportPriceWeaponStore;
FC_GAME_API extern DBCStorage <ItemPriceBaseEntry>           sItemPriceBaseStore;
FC_GAME_API extern DBCStorage <ItemReforgeEntry>             sItemReforgeStore;
FC_GAME_API extern DBCStorage <ItemArmorQualityEntry>        sItemArmorQualityStore;
FC_GAME_API extern DBCStorage <ItemArmorShieldEntry>         sItemArmorShieldStore;
FC_GAME_API extern DBCStorage <ItemArmorTotalEntry>          sItemArmorTotalStore;
FC_GAME_API extern DBCStorage <ItemClassEntry>               sItemClassStore;
FC_GAME_API extern DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageAmmoStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandCasterStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageRangedStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageThrownStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandCasterStore;
FC_GAME_API extern DBCStorage <ItemDamageEntry>              sItemDamageWandStore;
//FC_GAME_API extern DBCStorage <ItemDisplayInfoEntry>      sItemDisplayInfoStore; -- not used currently
FC_GAME_API extern DBCStorage <ItemDisenchantLootEntry>      sItemDisenchantLootStore;
FC_GAME_API extern DBCStorage <ItemLimitCategoryEntry>       sItemLimitCategoryStore;
FC_GAME_API extern DBCStorage <ItemRandomPropertiesEntry>    sItemRandomPropertiesStore;
FC_GAME_API extern DBCStorage <ItemRandomSuffixEntry>        sItemRandomSuffixStore;
FC_GAME_API extern DBCStorage <ItemSetEntry>                 sItemSetStore;
FC_GAME_API extern DBCStorage <LFGDungeonEntry>              sLFGDungeonStore;
FC_GAME_API extern DBCStorage <LFGDungeonsGroupingMapEntry>  sLFGDungeonsGroupingMapStore;
FC_GAME_API extern DBCStorage <LiquidTypeEntry>              sLiquidTypeStore;
FC_GAME_API extern DBCStorage <LockEntry>                    sLockStore;
FC_GAME_API extern DBCStorage <MailTemplateEntry>            sMailTemplateStore;
FC_GAME_API extern DBCStorage <MapEntry>                     sMapStore;
FC_GAME_API extern DBCStorage <MountCapabilityEntry>         sMountCapabilityStore;
FC_GAME_API extern DBCStorage <MountTypeEntry>               sMountTypeStore;
//FC_GAME_API extern DBCStorage <NameGenEntry>                 sNameGenStore; -- use GetRandomCharacterName instead
FC_GAME_API extern DBCStorage <NumTalentsAtLevelEntry>       sNumTalentsAtLevelStore;
FC_GAME_API extern DBCStorage <PhaseEntry>                   sPhaseStore;
FC_GAME_API extern DBCStorage <PhaseGroupEntry>              sPhaseGroupStore;
FC_GAME_API extern DBCStorage <LightEntry>                   sLightStore;
//FC_GAME_API extern DBCStorage <MapDifficultyEntry>           sMapDifficultyStore; -- use GetMapDifficultyData insteed
FC_GAME_API extern MapDifficultyMap                          sMapDifficultyMap;
FC_GAME_API extern DBCStorage <MovieEntry>                   sMovieStore;
FC_GAME_API extern DBCStorage <OverrideSpellDataEntry>       sOverrideSpellDataStore;
FC_GAME_API extern DBCStorage <PowerDisplayEntry>            sPowerDisplayStore;
FC_GAME_API extern DBCStorage <QuestSortEntry>               sQuestSortStore;
FC_GAME_API extern DBCStorage <QuestXPEntry>                 sQuestXPStore;
FC_GAME_API extern DBCStorage <QuestFactionRewEntry>         sQuestFactionRewardStore;
FC_GAME_API extern DBCStorage <QuestPOIPointEntry>           sQuestPOIPointStore;
FC_GAME_API extern DBCStorage <QuestPOIBlobEntry>            sQuestPOIBlobStore;
FC_GAME_API extern DBCStorage <RandomPropertiesPointsEntry>  sRandomPropertiesPointsStore;
FC_GAME_API extern DBCStorage <ResearchBranchEntry>          sResearchBranchStore;
FC_GAME_API extern DBCStorage <ResearchFieldEntry>           sResearchFieldStore;
FC_GAME_API extern DBCStorage <ResearchProjectEntry>         sResearchProjectStore;
FC_GAME_API extern DBCStorage <ResearchSiteEntry>            sResearchSiteStore;
FC_GAME_API extern DBCStorage <ScalingStatDistributionEntry> sScalingStatDistributionStore;
FC_GAME_API extern DBCStorage <ScalingStatValuesEntry>       sScalingStatValuesStore;
FC_GAME_API extern DBCStorage <SkillLineEntry>               sSkillLineStore;
FC_GAME_API extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
FC_GAME_API extern DBCStorage <SkillTiersEntry>              sSkillTiersStore;
FC_GAME_API extern DBCStorage <SoundEntriesEntry>            sSoundEntriesStore;
FC_GAME_API extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
FC_GAME_API extern DBCStorage <SpellCategoryEntry>           sSpellCategoryStore;
FC_GAME_API extern DBCStorage <SpellDifficultyEntry>         sSpellDifficultyStore;
FC_GAME_API extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
FC_GAME_API extern DBCStorage <SpellFocusObjectEntry>        sSpellFocusObjectStore;
FC_GAME_API extern DBCStorage <SpellItemEnchantmentEntry>    sSpellItemEnchantmentStore;
FC_GAME_API extern DBCStorage <SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore;
FC_GAME_API extern PetFamilySpellsStore                      sPetFamilySpellsStore;
FC_GAME_API extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
FC_GAME_API extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
FC_GAME_API extern DBCStorage <SpellRuneCostEntry>           sSpellRuneCostStore;
FC_GAME_API extern DBCStorage <SpellShapeshiftEntry>         sSpellShapeshiftStore;
FC_GAME_API extern DBCStorage <SpellShapeshiftFormEntry>     sSpellShapeshiftFormStore;
FC_GAME_API extern DBCStorage <SpellEntry>                   sSpellStore;
FC_GAME_API extern DBCStorage <SpellVisualEntry>             sSpellVisualStore;
FC_GAME_API extern DBCStorage <SpellVisualKitEntry>          sSpellVisualKitStore;
FC_GAME_API extern DBCStorage <SpellAuraOptionsEntry>        sSpellAuraOptionsStore;
FC_GAME_API extern DBCStorage <SpellAuraRestrictionsEntry>   sSpellAuraRestrictionsStore;
FC_GAME_API extern DBCStorage <SpellCastingRequirementsEntry> sSpellCastingRequirementsStore;
FC_GAME_API extern DBCStorage <SpellCategoriesEntry>         sSpellCategoriesStore;
FC_GAME_API extern DBCStorage <SpellClassOptionsEntry>       sSpellClassOptionsStore;
FC_GAME_API extern DBCStorage <SpellCooldownsEntry>          sSpellCooldownsStore;
FC_GAME_API extern DBCStorage <SpellEffectEntry>             sSpellEffectStore;
FC_GAME_API extern DBCStorage <SpellEquippedItemsEntry>      sSpellEquippedItemsStore;
FC_GAME_API extern DBCStorage <SpellInterruptsEntry>         sSpellInterruptsStore;
FC_GAME_API extern DBCStorage <SpellLevelsEntry>             sSpellLevelsStore;
FC_GAME_API extern DBCStorage <SpellPowerEntry>              sSpellPowerStore;
FC_GAME_API extern DBCStorage <SpellReagentsEntry>           sSpellReagentsStore;
FC_GAME_API extern DBCStorage <SpellScalingEntry>            sSpellScalingStore;
FC_GAME_API extern DBCStorage <SpellTargetRestrictionsEntry> sSpellTargetRestrictionsStore;
FC_GAME_API extern DBCStorage <SpellTotemsEntry>             sSpellTotemsStore;
FC_GAME_API extern DBCStorage <SummonPropertiesEntry>        sSummonPropertiesStore;
FC_GAME_API extern DBCStorage <TalentEntry>                  sTalentStore;
FC_GAME_API extern DBCStorage <TalentTabEntry>               sTalentTabStore;
FC_GAME_API extern DBCStorage <TaxiNodesEntry>               sTaxiNodesStore;
FC_GAME_API extern DBCStorage <TaxiPathEntry>                sTaxiPathStore;
FC_GAME_API extern TaxiMask                                  sTaxiNodesMask;
FC_GAME_API extern TaxiMask                                  sOldContinentsNodesMask;
FC_GAME_API extern TaxiMask                                  sHordeTaxiNodesMask;
FC_GAME_API extern TaxiMask                                  sAllianceTaxiNodesMask;
FC_GAME_API extern TaxiMask                                  sDeathKnightTaxiNodesMask;
FC_GAME_API extern TaxiPathSetBySource                       sTaxiPathSetBySource;
FC_GAME_API extern TaxiPathNodesByPath                       sTaxiPathNodesByPath;
FC_GAME_API extern DBCStorage <TransportAnimationEntry>      sTransportAnimationStore;
FC_GAME_API extern DBCStorage <TransportRotationEntry>       sTransportRotationStore;
FC_GAME_API extern DBCStorage <TotemCategoryEntry>           sTotemCategoryStore;
FC_GAME_API extern DBCStorage <UnitPowerBarEntry>            sUnitPowerBarStore;
FC_GAME_API extern DBCStorage <VehicleEntry>                 sVehicleStore;
FC_GAME_API extern DBCStorage <VehicleSeatEntry>             sVehicleSeatStore;
FC_GAME_API extern DBCStorage <WMOAreaTableEntry>            sWMOAreaTableStore;
FC_GAME_API extern DBCStorage <WorldMapAreaEntry>            sWorldMapAreaStore;
FC_GAME_API extern DBCStorage <WorldMapOverlayEntry>         sWorldMapOverlayStore;
FC_GAME_API extern DBCStorage <WorldSafeLocsEntry>           sWorldSafeLocsStore;

class FC_GAME_API DBCManager
{
public:
    static DBCManager& Instance();

    void LoadStores(const std::string& dataPath, uint32 defaultLocale);

    SimpleFactionsList const* GetFactionTeamList(uint32 faction);
    static char const* GetPetName(uint32 petfamily, uint32 dbclang);
    uint32 GetTalentSpellCost(uint32 spellId);
    TalentSpellPos const* GetTalentSpellPos(uint32 spellId);
    static char const* GetRaceName(uint8 race, uint8 locale);
    static char const* GetClassName(uint8 class_, uint8 locale);
    WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid);
    static uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);
    std::string const& GetRandomCharacterName(uint8 race, uint8 gender);
    static uint32 GetMaxLevelForExpansion(uint32 expansion);
    ContentLevels GetContentLevelsForMapAndZone(uint32 mapid, uint32 zoneId);
    static bool IsTotemCategoryCompatibleWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId);
    void Zone2MapCoordinates(float &x, float &y, uint32 zone);
    void Map2ZoneCoordinates(float &x, float &y, uint32 zone);
    MapDifficulty const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);
    MapDifficulty const* GetDownscaledMapDifficultyData(uint32 mapId, Difficulty &difficulty);
    uint32 const* /*[MAX_TALENT_TABS]*/ GetTalentTabPages(uint8 cls);
    std::vector<uint32> const* GetTalentTreePrimarySpells(uint32 talentTree);
    static uint32 GetLiquidFlags(uint32 liquidType);
    static uint32 GetDefaultMapLight(uint32 mapId);
    PvPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level);
    PvPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapid, BattlegroundBracketId id);
    CharStartOutfitEntry const* GetCharStartOutfitEntry(uint8 race, uint8 class_, uint8 gender);
    CharSectionsEntry const* GetCharSectionEntry(uint8 race, CharSectionType genType, uint8 gender, uint8 type, uint8 color);
    uint32 GetPowerIndexByClass(Powers power, uint32 classId);
    static bool IsInArea(uint32 objectAreaId, uint32 areaId);
    static LFGDungeonEntry const* GetLFGDungeon(uint32 mapId, Difficulty difficulty);
    std::vector<uint32> const* GetPhasesForGroup(uint32 group);
    std::vector<SkillLineAbilityEntry const*> const* GetSkillLineAbilitiesBySkill(uint32 skillId) const;
    SkillRaceClassInfoEntry const* GetSkillRaceClassInfo(uint32 skill, uint8 race, uint8 class_);
    ResponseCodes ValidateName(std::wstring const& name, LocaleConstant locale);
    EmotesTextSoundEntry const* FindTextSoundEmoteFor(uint32 emote, uint32 race, uint32 gender);
};

#define sDBCManager DBCManager::Instance()

#endif
