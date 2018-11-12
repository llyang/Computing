import java.util.Calendar;

public class test_date {

  public static void main(String[] args)
  {
    Calendar cal = Calendar.getInstance();
    cal.set(2000, 2 - 1, 29);

    int year = cal.get(Calendar.YEAR);
    int month = cal.get(Calendar.MONTH);
    int day = cal.get(Calendar.DAY_OF_MONTH);
    System.out.printf("%4d-%02d-%02d\n", year, month + 1, day);

    cal.add(Calendar.YEAR, 5);
    year = cal.get(Calendar.YEAR);
    month = cal.get(Calendar.MONTH);
    day = cal.get(Calendar.DAY_OF_MONTH);
    System.out.printf("%4d-%02d-%02d\n", year, month + 1, day);

    cal.add(Calendar.MONTH, 100);
    year = cal.get(Calendar.YEAR);
    month = cal.get(Calendar.MONTH);
    day = cal.get(Calendar.DAY_OF_MONTH);
    System.out.printf("%4d-%02d-%02d\n", year, month + 1, day);

    cal.add(Calendar.DAY_OF_MONTH, 1000);
    year = cal.get(Calendar.YEAR);
    month = cal.get(Calendar.MONTH);
    day = cal.get(Calendar.DAY_OF_MONTH);
    System.out.printf("%4d-%02d-%02d\n", year, month + 1, day);
  }
}
