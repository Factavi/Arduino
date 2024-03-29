/******************* our codes ************/

int VizioPowerSignal[] {
// ON, OFF (in 10's of microseconds)
	922, 462,
	60, 50,
	60, 52,
	60, 168,
	58, 54,
	60, 52,
	58, 52,
	58, 56,
	58, 52,
	60, 166,
	60, 166,
	58, 56,
	60, 166,
	56, 172,
	56, 170,
	56, 170,
	58, 170,
	58, 56,
	58, 52,
	58, 54,
	56, 170,
	56, 58,
	54, 56,
	58, 54,
	56, 56,
	54, 172,
	56, 170,
	58, 170,
	56, 58,
	52, 172,
	58, 170,
	56, 170,
	58, 170,
	56, 4248,
	922, 232,
	54, 0};

int VizioUpSignal[] = {
// ON, OFF (in 10's of microseconds)
	924, 462,
	54, 56,
	56, 56,
	54, 172,
	54, 60,
	54, 56,
	56, 56,
	54, 58,
	54, 58,
	54, 172,
	54, 172,
	54, 60,
	54, 172,
	54, 172,
	56, 172,
	54, 172,
	54, 174,
	54, 172,
	56, 58,
	54, 172,
	54, 58,
	56, 56,
	54, 56,
	54, 174,
	58, 54,
	54, 58,
	58, 168,
	58, 54,
	56, 170,
	54, 174,
	54, 172,
	54, 60,
	58, 168,
	58, 4226,
	924, 232,
	58, 0};

int VizioDownSignal[] = {
// ON, OFF (in 10's of microseconds)
	928, 458,
	58, 52,
	54, 56,
	60, 168,
	58, 54,
	60, 52,
	54, 60,
	50, 56,
	62, 52,
	54, 172,
	54, 174,
	54, 58,
	60, 166,
	54, 174,
	58, 168,
	60, 168,
	54, 172,
	54, 60,
	54, 172,
	54, 172,
	60, 54,
	58, 52,
	54, 58,
	54, 172,
	54, 60,
	58, 170,
	52, 58,
	58, 52,
	56, 172,
	54, 172,
	56, 172,
	56, 56,
	60, 166,
	60, 4230,
	928, 228,
	60, 0};

int VizioLeftSignal[] = {
// ON, OFF (in 10's of microseconds)
	922, 464,
	54, 56,
	54, 58,
	54, 172,
	54, 60,
	54, 56,
	54, 60,
	52, 58,
	54, 56,
	56, 172,
	54, 172,
	54, 60,
	54, 172,
	52, 174,
	54, 172,
	56, 172,
	54, 174,
	54, 172,
	54, 174,
	54, 172,
	54, 60,
	54, 56,
	54, 58,
	54, 172,
	58, 56,
	50, 60,
	52, 60,
	52, 60,
	52, 174,
	58, 168,
	60, 168,
	58, 56,
	58, 166,
	58, 4234,
	926, 228,
	60, 0};

int VizioRightSignal[] = {
// ON, OFF (in 10's of microseconds)
	920, 466,
	54, 58,
	56, 54,
	54, 172,
	58, 56,
	54, 56,
	56, 56,
	56, 56,
	54, 58,
	54, 172,
	54, 174,
	54, 58,
	54, 172,
	54, 172,
	56, 172,
	54, 172,
	54, 174,
	56, 58,
	50, 60,
	54, 56,
	58, 170,
	54, 58,
	52, 60,
	54, 172,
	54, 60,
	50, 174,
	54, 174,
	54, 172,
	58, 56,
	52, 174,
	54, 172,
	54, 60,
	54, 172,
	56, 4234,
	922, 232,
	56, 0};

int VizioCenterSignal[] = {
// ON, OFF (in 10's of microseconds)
	922, 464,
	54, 56,
	54, 60,
	50, 174,
	54, 60,
	52, 58,
	54, 56,
	54, 60,
	54, 56,
	54, 172,
	56, 172,
	54, 60,
	56, 170,
	52, 174,
	54, 172,
	56, 172,
	54, 174,
	54, 172,
	58, 170,
	54, 58,
	58, 54,
	54, 56,
	54, 58,
	56, 170,
	56, 58,
	54, 56,
	56, 56,
	54, 172,
	54, 174,
	54, 172,
	54, 174,
	54, 58,
	56, 164,
	60, 4232,
	922, 232,
	54, 0};

 int VizioInfoSignal[] = {
// ON, OFF (in 10's of microseconds)
 924, 458,
  54, 58,
  54, 56,
  54, 174,
  54, 58,
  58, 52,
  56, 56,
  54, 60,
  56, 54,
  54, 172,
  54, 174,
  54, 58,
  58, 168,
  54, 174,
  54, 172,
  54, 174,
  54, 172,
  54, 174,
  54, 172,
  54, 60,
  58, 168,
  54, 172,
  54, 60,
  56, 54,
  54, 58,
  52, 60,
  58, 54,
  54, 172,
  54, 58,
  58, 54,
  56, 170,
  54, 172,
  56, 172,
  54, 4268,
  926, 228,
  58, 3358,
  926, 230,
  56, 3358,
  926, 230,
  54, 0};

  int VizioHDMISignal[] = {
// ON, OFF (in 10's of microseconds)
  926, 460,
  50, 60,
  54, 58,
  58, 168,
  58, 56,
  58, 52,
  58, 54,
  58, 54,
  58, 54,
  58, 168,
  58, 168,
  58, 56,
  58, 168,
  58, 168,
  58, 170,
  58, 168,
  58, 170,
  58, 54,
  58, 168,
  58, 168,
  60, 54,
  60, 50,
  60, 52,
  58, 170,
  58, 168,
  58, 170,
  58, 54,
  58, 54,
  58, 170,
  56, 0};


