// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// Thanks and Credits for Technologies found in BeepMagnet: Bitcoin, Novacoin, Blackcoin, Bitmessage, Shadowcoin, Cryptonote
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

//#include "chainparamsseeds.h"

unsigned int pnSeed[] =
{
    0x9778f9c0,
    0x9e45d090,
};


int64_t CChainParams::GetProofOfWorkReward(int nHeight, int64_t nFees) const
{
    // miner's coin base reward
    int64_t nSubsidy = 0;
    
    if (nHeight <= 0)
        nSubsidy = 0;
    else
    if (nHeight <= nDistributionFund)
        nSubsidy = 2000000 * COIN;
	else
    if (nHeight <= nLastFairLaunchBlock)
        nSubsidy = 1 * COIN;
    else
    if (nHeight <= nLastPOWBlock)
        nSubsidy = 15999.9 * COIN;
    
    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfWorkReward() : create=%s nSubsidy=%d\n", FormatMoney(nSubsidy).c_str(), nSubsidy);
    
    return nSubsidy + nFees;
};


int64_t CChainParams::GetProofOfStakeReward(int64_t nCoinAge, int64_t nFees) const
{
    // miner's coin stake reward based on coin age spent (coin-days)
    int64_t nSubsidy = nCoinAge * MCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);

    if (pindexBest->nHeight <= nFirstYearStake)
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nFirstBlockHalve)
        nSubsidy = nCoinAge * SCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nSecondBlockHalve)
        nSubsidy = nCoinAge * CCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nThirdBlockHalve)
        nSubsidy = nCoinAge * KCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nFourthBlockHalve)
        nSubsidy = nCoinAge * ICOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nFifthBlockHalve)
        nSubsidy = nCoinAge * OCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nSixthBlockHalve)
        nSubsidy = nCoinAge * DCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nSeventhBlockHalve)
        nSubsidy = nCoinAge * RCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nEighthBlockHalve)
        nSubsidy = nCoinAge * ECOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nNinthBlockHalve)
        nSubsidy = nCoinAge * ACOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
//    else
//    if (pindexBest->nHeight <= nTenthBlockHalve)
//        nSubsidy = nCoinAge * MCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);


    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfStakeReward(): create=%s nCoinAge=%d\n", FormatMoney(nSubsidy).c_str(), nCoinAge);

    return nSubsidy + nFees;
}
//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Convert the pnSeeds6 array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, unsigned int *data, unsigned int count, int port)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in_addr ip;
        memcpy(&ip, &pnSeed[i], sizeof(ip));
        CAddress addr(CService(ip, Params().GetDefaultPort()));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0xf0;
        pchMessageStart[2] = 0x0f;
        pchMessageStart[3] = 0x69;
        
        vAlertPubKey = ParseHex("0482299e1ba91b8d726160247ff58cf8aa8030054e778c496a1271d190414d1e5babeb9fbb2ec594cbde7d299cb2d529f9dcee06d180315eec72c532b40dff1e5f");
        
        nDefaultPort = 10340;
        nRPCPort = 10430;
        
        nFirstPosv2Block = 50000;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1); // proof-of-work difficulty
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 48);
        
        const char* pszTimestamp = "New York Times, Oct 25 2018: How Many Space Stations Does This Planet Need?";
        CTransaction txNew;
        txNew.nTime = GENESIS_BLOCK_TIME;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = GENESIS_BLOCK_TIME;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1;

        hashGenesisBlock = genesis.GetHash();

/*                                //------------------------------
                                if(genesis.GetHash() != uint256("0x"))
                                        {
                                            printf("Searching for genesis block...\n");
                                            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                                            while(uint256(genesis.GetHash()) > hashTarget)
                                            {
                                                ++genesis.nNonce;
                                                if (genesis.nNonce == 0)
                                                {
                                                    printf("NONCE WRAPPED, incrementing time");
                                                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                                    ++genesis.nTime;
                                                }
                                                if (genesis.nNonce % 10000 == 0)
                                                {
                                                    printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                                                }
                                            }
                                            printf("block.nTime = %u \n", genesis.nTime);
                                            printf("block.nNonce = %u \n", genesis.nNonce);
                                            printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                                        }
                                //------------------------------
                        printf("merkle root.GetHash = %s\n", genesis.hashMerkleRoot.ToString().c_str());
*/

        assert(hashGenesisBlock == uint256("0x4fded27e06775a822ae070ce320afd7783b58be72665a300ce452b9d52b67032"));
        assert(genesis.hashMerkleRoot == uint256("0x5a56d46af7fc77b5cf08a281345f1c79f97a0e7017bc7ddb9061ed59ff59ae0f"));
        
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("seed1.bmct.io", "seed2.bmct.io"));
        //vSeeds.push_back(CDNSSeedData("beepmagnetcoin.com", "dnsseed.beepmagnetcoin.com"));
        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(25)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(52)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(199)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x03)(0xCC)(0x23)(0xD7).convert_to_container<std::vector<unsigned char> >();  // need to change, to  okub
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x03)(0xCC)(0x1C)(0x73).convert_to_container<std::vector<unsigned char> >();  // need to change to okpv
        
        // TODO: There has yet to become a valid list of peers, come back to this once established.
        // convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        // convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        
        //nTenthBlockHalve = 15406453; // + 4 year blocks average                  x 0.655
        nNinthBlockHalve = 13281425; // + 4 year blocks average                   x 0.75
        nEighthBlockHalve = 11156397; // + 4 year blocks average                  x 1
        nSeventhBlockHalve = 9031369; // + 4 year blocks average                 x 1.25
        nSixthBlockHalve = 6906341; // + 4 year blocks average                      x 1.5
        nFifthBlockHalve = 4781313; // + 4 year blocks average                       x 3
        nFourthBlockHalve = 2656285; // + 1 year blocks average                    x 6
        nThirdBlockHalve = 2125028; // + 1 year blocks average                      x 6.25
        nSecondBlockHalve = 1593771; // + 1 year blocks average                   x 6.5
        nFirstBlockHalve = 1062514; // + 1 year blocks average                    x 6.75
        nFirstYearStake = 531257;  // 501257 blocks/year                          x 7
        
        nLastPOWBlock = 551;
        nLastFairLaunchBlock = 51;
        nDistributionFund = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const std::vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    std::vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x00;
        pchMessageStart[1] = 0x09;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x0f;
        
        nFirstPosv2Block = 50000;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 2);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 16);
        
        vAlertPubKey = ParseHex("04c20398b68bda9178e6b2ff4cddc8188608b9274921539e65af6e3b3199fbd8d3d9069d2c154aa3dbd54f89cd0bd8c04f0ba39bb100bc8ae25af2cf7fae21fd6c");
        nDefaultPort = 7980;
        nRPCPort = 7979;
        strDataDir = "testnet";

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();

/*                                       //------------------------------
                                        if(genesis.GetHash() != uint256("0x"))
                                                {
                                                    printf("Searching for genesis block...\n");
                                                    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                                                    while(uint256(genesis.GetHash()) > hashTarget)
                                                    {
                                                        ++genesis.nNonce;
                                                        if (genesis.nNonce == 0)
                                                        {
                                                            printf("NONCE WRAPPED, incrementing time");
                                                            std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                                            ++genesis.nTime;
                                                        }
                                                        if (genesis.nNonce % 10000 == 0)
                                                        {
                                                            printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                                                        }
                                                    }
                                                    printf(" TESTNET/nblock.nTime = %u \n", genesis.nTime);
                                                    printf("block.nNonce = %u \n", genesis.nNonce);
                                                    printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                                                }
                                        //------------------------------
                                printf("merkle root.GetHash = %s\n", genesis.hashMerkleRoot.ToString().c_str());
*/

        assert(hashGenesisBlock == uint256("0x21a6c4575bb5d3c3b1d422d685d3566610a383f63b45e1b175ad53f3cf3f02de"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(34)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(39)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(161)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x34)(0x18)(0xBB).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x34)(0x11)(0x56).convert_to_container<std::vector<unsigned char> >();
        
        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        // convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        //nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0x6b;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0xaa;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1540465498;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();

/*                                       //------------------------------
                                        if(genesis.GetHash() != uint256("0x"))
                                                {
                                                    printf("Searching for genesis block...\n");
                                                    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                                                    while(uint256(genesis.GetHash()) > hashTarget)
                                                    {
                                                        ++genesis.nNonce;
                                                        if (genesis.nNonce == 0)
                                                        {
                                                            printf("NONCE WRAPPED, incrementing time");
                                                            std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                                                            ++genesis.nTime;
                                                        }
                                                        if (genesis.nNonce % 10000 == 0)
                                                        {
                                                            printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                                                        }
                                                    }
                                                    printf(" REGTEST\nblock.nTime = %u \n", genesis.nTime);
                                                    printf("block.nNonce = %u \n", genesis.nNonce);
                                                    printf("block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
                                                }
                                        //------------------------------
                                printf("merkle root.GetHash = %s\n", genesis.hashMerkleRoot.ToString().c_str());
*/

        nDefaultPort = 8989;
        strDataDir = "regtest";



        assert(hashGenesisBlock == uint256("0x2a4778fc9de976ae38f7667097bd1d52d87d786d24a8a01c18160e9663d8a43a"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

const CChainParams &TestNetParams() {
    return testNetParams;
}

const CChainParams &MainNetParams() {
    return mainParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    };
};

bool SelectParamsFromCommandLine()
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest)
    {
        return false;
    };

    if (fRegTest)
    {
        SelectParams(CChainParams::REGTEST);
    } else
    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    } else
    {
        SelectParams(CChainParams::MAIN);
    };
    
    return true;
}
