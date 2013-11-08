SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `mydb` ;
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Staff`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Staff` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Staff` (
  `StaffId` VARCHAR(10) NOT NULL,
  `Forename` VARCHAR(45) NULL,
  `Surname` VARCHAR(45) NULL,
  PRIMARY KEY (`StaffId`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Advisor`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Advisor` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Advisor` (
  `StaffId` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`StaffId`),
  CONSTRAINT `fk_Advisor_Staff1`
    FOREIGN KEY (`StaffId`)
    REFERENCES `mydb`.`Staff` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Degree`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Degree` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Degree` (
  `Name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Student`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Student` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Student` (
  `Matric` VARCHAR(8) NOT NULL,
  `Email` VARCHAR(255) NULL,
  `Password` VARCHAR(32) NOT NULL,
  `Forename` VARCHAR(45) NULL,
  `Surname` VARCHAR(45) NULL,
  `Year` INT NULL,
  `AdvisorStaffId` VARCHAR(10) NOT NULL,
  `DegreeName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Matric`),
  INDEX `fk_Student_Advisor1_idx` (`AdvisorStaffId` ASC),
  INDEX `fk_Student_Degree1_idx` (`DegreeName` ASC),
  CONSTRAINT `fk_Student_Advisor1`
    FOREIGN KEY (`AdvisorStaffId`)
    REFERENCES `mydb`.`Advisor` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Student_Degree1`
    FOREIGN KEY (`DegreeName`)
    REFERENCES `mydb`.`Degree` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `mydb`.`College`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`College` ;

CREATE TABLE IF NOT EXISTS `mydb`.`College` (
  `Name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`School`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`School` ;

CREATE TABLE IF NOT EXISTS `mydb`.`School` (
  `Name` VARCHAR(45) NOT NULL,
  `CollegeName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`, `CollegeName`),
  INDEX `fk_School_College1_idx` (`CollegeName` ASC),
  CONSTRAINT `fk_School_College1`
    FOREIGN KEY (`CollegeName`)
    REFERENCES `mydb`.`College` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`DeptHead`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`DeptHead` ;

CREATE TABLE IF NOT EXISTS `mydb`.`DeptHead` (
  `StaffId` VARCHAR(10) NOT NULL,
  `Year` VARCHAR(45) NULL,
  `SchoolName` VARCHAR(45) NOT NULL,
  `SchoolCollegeName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`StaffId`),
  INDEX `fk_Dept Head_School1_idx` (`SchoolName` ASC, `SchoolCollegeName` ASC),
  CONSTRAINT `fk_Dept Head_Staff1`
    FOREIGN KEY (`StaffId`)
    REFERENCES `mydb`.`Staff` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Dept Head_School1`
    FOREIGN KEY (`SchoolName` , `SchoolCollegeName`)
    REFERENCES `mydb`.`School` (`Name` , `CollegeName`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`TeachingCommittee`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`TeachingCommittee` ;

CREATE TABLE IF NOT EXISTS `mydb`.`TeachingCommittee` (
  `StaffId` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`StaffId`),
  CONSTRAINT `fk_Teaching Committee_Staff1`
    FOREIGN KEY (`StaffId`)
    REFERENCES `mydb`.`Staff` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Course`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Course` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Course` (
  `CourseId` VARCHAR(7) NOT NULL,
  `Name` VARCHAR(45) NULL,
  `Aims` VARCHAR(45) NULL,
  `SchoolName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`CourseId`),
  INDEX `fk_Course_School1_idx` (`SchoolName` ASC),
  CONSTRAINT `fk_Course_School1`
    FOREIGN KEY (`SchoolName`)
    REFERENCES `mydb`.`School` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`StudentHasCourse`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`StudentHasCourse` ;

CREATE TABLE IF NOT EXISTS `mydb`.`StudentHasCourse` (
  `StudentHasCourseId` VARCHAR(45) NOT NULL,
  `StudentMatric` VARCHAR(8) NOT NULL,
  `CourseId` VARCHAR(7) NOT NULL,
  PRIMARY KEY (`StudentHasCourseId`),
  INDEX `fk_Student_has_Course_Student1_idx` (`StudentMatric` ASC),
  INDEX `fk_Student_has_Course_Course1_idx` (`CourseId` ASC),
  CONSTRAINT `fk_Student_has_Course_Student1`
    FOREIGN KEY (`StudentMatric`)
    REFERENCES `mydb`.`Student` (`Matric`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Student_has_Course_Course1`
    FOREIGN KEY (`CourseId`)
    REFERENCES `mydb`.`Course` (`CourseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `mydb`.`DegreeHasCourse`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`DegreeHasCourse` ;

CREATE TABLE IF NOT EXISTS `mydb`.`DegreeHasCourse` (
  `DegreeHasCourseId` VARCHAR(45) NOT NULL,
  `DegreeName` VARCHAR(45) NOT NULL,
  `CourseId` VARCHAR(7) NOT NULL,
  PRIMARY KEY (`DegreeHasCourseId`),
  INDEX `fk_Degree_has_Course_Degree1_idx` (`DegreeName` ASC),
  INDEX `fk_Degree_has_Course_Course1_idx` (`CourseId` ASC),
  CONSTRAINT `fk_Degree_has_Course_Degree1`
    FOREIGN KEY (`DegreeName`)
    REFERENCES `mydb`.`Degree` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Degree_has_Course_Course1`
    FOREIGN KEY (`CourseId`)
    REFERENCES `mydb`.`Course` (`CourseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
