// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
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

#include "chainparamsseeds.h"

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
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x5a;
        pchMessageStart[1] = 0x9e;
        pchMessageStart[2] = 0x2b;
        pchMessageStart[3] = 0x47;
        vAlertPubKey = ParseHex("04e80695c62f7c2f81f85d251a216df3be197653f454852a2d08c631aad5ca3cbe5616262ca3e7a6feef6a54765b96e9056bc6b132a04b94acefeac5d5257fe028");
        nDefaultPort = 16969;
        nRPCPort = 16968;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "https://www.rt.com/news/405288-erdogan-eu-turkey-speech"; // ‘EU failed us, Turkey doesn’t need it anymore,’ says Erdogan
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1506946020, vin, vout, 0); 
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1506946020; 
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 536192;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x28a26245c8468f3460fad6283a22d5307e6ffc8e795992586c52a5ef97bf4d4e"));
        assert(genesis.hashMerkleRoot == uint256("0x94c24a215448c39c25d020ceb6ed37fa4cb70bfabf3b45091876a6d027746537"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,69);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,96);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,99);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x99)(0xA9)(0x3C).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x99)(0x6E)(0xD1).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 69; // Initially ~569 Sec during PoW
        if(nBestHeight > nLastPoWBlock) // Scaled down for PoS only phase
        {
          nTargetSpacing = 40;
        }

        nTargetTimespan = 18 * nTargetSpacing;
        nLastPoWBlock = 6969;
        nStartPoSBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0x0d;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0x81;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("04e80695c62f7c2f81f85d251a216df3be197653f454852a2d08c631aad5ca3cbe5616262ca3e7a6feef6a54765b96e9056bc6b132a04b94acefeac5d5257fe028");
        nDefaultPort = 26969;
        nRPCPort = 26968;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 79462;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x7f9ec789f67fd16fca0f73242106ca69c7e4e3e2d5e46fafa1491ae2086d8da3"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,71);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,116);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,53);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x66)(0x4F)(0x8C).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x55)(0xEA)(0x7B).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 69;
        nLastPoWBlock = 690;
        nStartPoSBlock = 1;
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
        pchMessageStart[0] = 0x71;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0xc2;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1506946020;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 9087;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 16970;
        strDataDir = "regtest";

        assert(hashGenesisBlock == uint256("0x9a8508acb6595f985c8a7b8f39f93ee101165165b9c3d36dac86e9c9cc9f8167"));

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

void SelectParams(CChainParams::Network network) {
    switch (network) {
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
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
