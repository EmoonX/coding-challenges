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

const birthday: string = process.argv[2];
const dateBirth = new Date(birthday);
console.log(dateBirth);

const dateNow = new Date();
console.log(dateNow);


