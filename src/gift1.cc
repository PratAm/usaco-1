/*
ID: joao.c.1
PROG: gift1
LANG: C++
*/

#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct GroupMember {
    string name;
    int initialMoneyValue;
    int finalMoneyValue;
    vector<string> giftRecipients;
};

GroupMember * getGroupMember(vector<GroupMember> & groupMembers, string name) {
    for (unsigned int i = 0; i < groupMembers.size(); i++) {
        if (groupMembers[i].name == name)
            return &groupMembers[i];
    }
    return NULL;
}

void giveGifts(vector<GroupMember> & groupMembers, GroupMember * gm) {
    if (gm->giftRecipients.size() > 0) {
        int amountToGive = gm->initialMoneyValue / gm->giftRecipients.size();
        int amountGiven = 0;
        for (unsigned int i = 0; i < gm->giftRecipients.size(); i++) {
            GroupMember * recipient = getGroupMember(groupMembers,
                                                     gm->giftRecipients[i]);
            recipient->finalMoneyValue += amountToGive;
            amountGiven += amountToGive;
        }
        gm->finalMoneyValue += (gm->initialMoneyValue - amountGiven);
    }
}

int main() {
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");

    vector<GroupMember> groupMembers;
    int NP;
    fin >> NP; fin.ignore();
    for (int i = 0; i < NP; i++) {
        GroupMember gm;
        getline(fin, gm.name);
        gm.initialMoneyValue = 0;
        gm.finalMoneyValue = 0;

        groupMembers.push_back(gm);
    }

    for (int i = 0; i < NP; i++) {
        string personName;
        getline(fin, personName);
        GroupMember * gm = getGroupMember(groupMembers, personName);

        int NG;
        fin >> gm->initialMoneyValue >> NG; fin.ignore();
        for (int j = 0; j < NG; j++) {
            string giftRecipientName;
            getline(fin, giftRecipientName);

            gm->giftRecipients.push_back(giftRecipientName);
        }
    }

    for (int i = 0; i < NP; i++) {
        giveGifts(groupMembers, &groupMembers[i]);
    }

    for (int i = 0; i < NP; i++) {
        fout << groupMembers[i].name << " "
             << (groupMembers[i].finalMoneyValue - groupMembers[i].initialMoneyValue) << endl;
    }

    return 0;
}
