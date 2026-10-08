#ifndef PDG_WEBTRANSPORT_H
#define PDG_WEBTRANSPORT_H
#ifdef __cplusplus
extern "C" {
#endif
// JSON requests/results are owned copies. No callbacks into JavaScript occur here.
char *pdg_wt_command(const char *request);
void pdg_wt_free(char *result);
void pdg_wt_suspend(void);
#ifdef __cplusplus
}
#endif
#endif
