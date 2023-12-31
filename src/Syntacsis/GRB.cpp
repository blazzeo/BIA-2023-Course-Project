#include "GRB.h"
#include "Rules.h"
#include "stdio.h"
#include "string.h"
#include <vector>

namespace GRB
{
	Rule::Chain::Chain(std::vector<GRBALPHABET> vec)
	{
		this->nt = new GRBALPHABET[this->size = vec.size()];

		for (int i = 0; i < this->size; i++)
            this->nt[i] = vec[i];
	}

	Rule::Rule(GRBALPHABET pnn, int iderroe, std::vector<Chain> vec)
	{
		this->nn = pnn;
		this->iderror = iderroe;
		this->chains = new Chain[this->size = vec.size()];
		for (int i = 0; i < this->size; i++)
			this->chains[i] = vec[i];
	}
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, std::vector<Rule> vec)
	{
		this->startN = pstartN;
		this->stbottomT = pstbottomT;
		this->rules = new Rule[this->size = vec.size()];
		for (int i = 0; i < this->size; i++)
			rules[i] = vec[i];
	}

std::vector<GRBALPHABET> grb(const std::string& str) {
  std::vector<GRBALPHABET> grb;
  for(auto lexem : str) {
    if (lexem >= 'A' && lexem <= 'Z') {
      grb.push_back(NS(lexem));
    } else grb.push_back(TS(lexem));
  }
  return grb;
}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < this->size && rules[k].nn != pnn)
			k++;
		if (k < this->size)
			prule = rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
			rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		this->chains[nchain].getCChain(buf);
		// strcat(b, buf);
		strncat(b, buf, sizeof(buf) + 5);

		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;

		while (j < this->size && this->chains[j].nt && this->chains[j].nt[0] != t) {
			j++;
        }

		rc = (j < this->size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->size; i++)
			b[i] = Chain::alphabet_to_char(this->nt[i]);
		b[this->size] = 0;
		return b;
	}
	Greibach getGreibach()
	{
		return greibach;
	}
}
