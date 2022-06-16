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

const year: number = parseInt(process.argv[2]);
console.log(year);
console.log(isLeapYear(year));
