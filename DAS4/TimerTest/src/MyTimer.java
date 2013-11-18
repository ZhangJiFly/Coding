import java.util.Timer;
import java.util.TimerTask;
import java.util.Calendar;

  public class MyTimer {

    private Timer timer;

    /**
     * constructor
     *
     * - starts a timer that fires at the next 5 minute boundary and
     *   every 5 minutes after that
     */

    public MyTimer() {

      long delay, period;
      Calendar cal=Calendar.getInstance(); // get today
      int hr = cal.get(Calendar.HOUR_OF_DAY);
      int mn = cal.get(Calendar.MINUTE);
      mn = 5 * (mn / 5 + 1);	// round up to next 5 minute slot
      if (mn == 60) {
        hr = hr + 1; mn = 0;
      }
      cal.set(Calendar.HOUR_OF_DAY,hr);
      cal.set(Calendar.MINUTE,mn);
      cal.set(Calendar.SECOND,0);
      // milliseconds until next 5 minute boundary
      delay = cal.getTimeInMillis() - System.currentTimeMillis();
      System.out.format("%04d\n", delay);
      period = 5 * 60 * 1000;	// 5 minutes in milliseconds
      System.err.format("Seconds of delay  = %d.%03d\n", delay/1000, delay%1000);
      System.err.format("period = %d.%03d\n", period/1000, period%1000);
      timer = new Timer();
      timer.scheduleAtFixedRate(new RepeatTask(), delay, period);
    }

    /**
     * task that is scheduled by the timer
     */
    class RepeatTask extends TimerTask {
      public void run() {
        Calendar now = Calendar.getInstance();
        System.out.format("%04d%02d%02d-%02d%02d%02d\n",
                          now.get(Calendar.YEAR),
                          now.get(Calendar.MONTH),
                          now.get(Calendar.DAY_OF_MONTH),
                          now.get(Calendar.HOUR_OF_DAY),
                          now.get(Calendar.MINUTE),
                          now.get(Calendar.SECOND));
      }
    }
    
    public static void main(String[] args){
    	new MyTimer();
    }
  }
