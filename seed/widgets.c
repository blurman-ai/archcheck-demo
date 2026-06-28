
#include <stdio.h>

/* Each seed function calls its OWN distinctive helpers, so its call names are rare
   (low df) and a copy — even renamed — stays a candidacy match. (Shared helpers
   would inflate df past the rare-token cap and defeat rename candidacy; #070/§3.) */
extern int alpha_frobnicate_xa(int, int);
extern int alpha_quux_xa(int);
extern int beta_zorp_xb(int, int, int);
extern int beta_blint_xb(int);
extern int gamma_warp_xc(int, int);
extern int gamma_mux_xc(int);
extern int delta_splice_xd(int, int);
extern int delta_churn_xd(int);

int alpha_distinct_compute(int wibble, int wobble) {
  int accumulator = alpha_frobnicate_xa(wibble, wobble);
  for (int idx = 0; idx < wibble; ++idx) {
    accumulator += alpha_quux_xa(idx);
    accumulator -= alpha_frobnicate_xa(idx, wibble);
  }
  return alpha_quux_xa(accumulator);
}

int beta_distinct_resolve(int snarf, int blorb) {
  int total = beta_zorp_xb(snarf, blorb, snarf);
  for (int k = 0; k < blorb; ++k) {
    total += beta_blint_xb(k);
    total = beta_zorp_xb(total, k, blorb);
  }
  return total + beta_blint_xb(blorb);
}

int gamma_distinct_evaluate(int plonk, int gribble) {
  int sum = gamma_mux_xc(plonk);
  for (int j = 0; j < gribble; ++j) {
    sum += gamma_warp_xc(j, plonk);
    sum = gamma_mux_xc(sum);
  }
  return gamma_warp_xc(sum, gribble);
}

int delta_distinct_collate(int florp, int wuzzle) {
  int agg = delta_churn_xd(florp);
  for (int m = 0; m < wuzzle; ++m) {
    agg += delta_splice_xd(m, florp);
    agg -= delta_churn_xd(m);
  }
  return delta_splice_xd(agg, wuzzle);
}
