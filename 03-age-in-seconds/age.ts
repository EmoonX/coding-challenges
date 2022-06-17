/** How many seconds in a day. */
const SECONDS_PER_DAY = 60 * 60 * 24;

/** Default number of days in each month. */
const daysInMonth = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

/** Checks if given year is a leap year. */
function isLeapYear(year: number): boolean {
  if (year % 4 == 0) {
    if (year % 100 == 0) {
      return year % 400 == 0;
    }
    return true;
  }
  return false;
}

/** Gets total amount of days for the month of given date. */
function getTotalDaysInMonth(date: Date): number {
  const monthIndex = date.getMonth();
  if (date.getMonth() == 1 && isLeapYear(date.getFullYear())) {
    return 29;
  }
  return daysInMonth[monthIndex];
}

/** Calculates total number of seconds between given dates within a year. */
function calculateInYear(start: Date, end: Date): number {
  let seconds = 0;
  seconds += 60 * 60 * (23 - start.getHours());
  seconds += 60 * (59 - start.getMinutes());
  seconds += 60 - start.getSeconds();
  if (start.getMonth() == end.getMonth()) {
    const fullDays = end.getDate() - start.getDate() - 1;
    seconds += fullDays * SECONDS_PER_DAY;
  } else {
    const startMonthFullDays = getTotalDaysInMonth(start) - start.getDate();
    seconds += startMonthFullDays * SECONDS_PER_DAY;
    const date = start;
    for (let month = start.getMonth() + 1; month < end.getMonth(); month++) {
      date.setMonth(month);
      const totalDays = getTotalDaysInMonth(date);
      seconds += totalDays * SECONDS_PER_DAY;
    }
    const endMonthFullDays = end.getDate() - 1;
    seconds += endMonthFullDays * SECONDS_PER_DAY;
  }
  seconds += 60 * 60 * end.getHours();
  seconds += 60 * end.getMinutes();
  seconds += end.getSeconds();
  return seconds;
}

/** Calculates total number of seconds between two dates. */
function calculate(birth: Date, now: Date): number {
  if (birth.getFullYear() === now.getFullYear()) {
    return calculateInYear(birth, now);
  }
  let seconds = calculateInYear(
    birth, new Date(`${birth.getFullYear()}-12-31 23:59:59`)
  ) + 1;
  for (let year = birth.getFullYear() + 1; year < now.getFullYear(); year++) {
    const daysInYear = isLeapYear(year) ? 366 : 365;
    seconds += daysInYear * SECONDS_PER_DAY;
  }
  const aux = calculateInYear(
    new Date(`${now.getFullYear()}-01-01 00:00:00`), now
  );
  seconds += aux;
  return seconds;
}

// Get birthday date and current date
const birthday: string = process.argv[2];
console.log(`> You were born in ${birthday}.`);
const dateBirth = new Date(`${birthday} 12:00:00`);
const dateNow = new Date();

// Calculate result and print it
console.log('> Your age is approximately:');
const seconds = calculate(dateBirth, dateNow);
const minutes = seconds / 60;
const hours = minutes / 60;
const days = hours / 24;
const months = days / 30;
const years = days / 365;
console.log(`  • ${Math.round(years)} years...`);
console.log(`  • ${Math.round(months)} months...`);
console.log(`  • ${Math.round(days)} days...`);
console.log(`  • ${Math.round(hours)} hours...`);
console.log(`  • ${Math.round(minutes)} minutes...`);
console.log(`  • or ${seconds} seconds!\n`);
