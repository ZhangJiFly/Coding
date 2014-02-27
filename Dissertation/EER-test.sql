SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `mydb` ;
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`College`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`College` (
  `Name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`School`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`School` (
  `Name` VARCHAR(45) NOT NULL,
  `College` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Name`),
  INDEX `fk_School_College1_idx` (`College` ASC),
  CONSTRAINT `fk_School_College1`
    FOREIGN KEY (`College`)
    REFERENCES `mydb`.`College` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Staff`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Staff` (
  `StaffId` VARCHAR(10) NOT NULL,
  `Forename` VARCHAR(45) NOT NULL,
  `Surname` VARCHAR(45) NOT NULL,
  `Email` VARCHAR(45) NOT NULL,
  `Password` VARCHAR(500) NULL,
  `Salt` VARCHAR(200) NULL,
  `Username` VARCHAR(45) NULL,
  `School` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`StaffId`, `School`),
  INDEX `fk_Staff_School1_idx` (`School` ASC),
  CONSTRAINT `fk_Staff_School1`
    FOREIGN KEY (`School`)
    REFERENCES `mydb`.`School` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Advisor`
-- -----------------------------------------------------
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
CREATE TABLE IF NOT EXISTS `mydb`.`Degree` (
  `Name` VARCHAR(45) NOT NULL,
  `School` VARCHAR(45) NOT NULL,
  `Years` INT NULL,
  `DegreeType` ENUM('BA','BEng','BSci','MA','MEng', 'MSci') NULL,
  PRIMARY KEY (`Name`, `School`),
  INDEX `fk_Degree_School1_idx` (`School` ASC),
  CONSTRAINT `fk_Degree_School1`
    FOREIGN KEY (`School`)
    REFERENCES `mydb`.`School` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Student`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Student` (
  `Matric` VARCHAR(8) NOT NULL,
  `Email` VARCHAR(255) NULL,
  `Password` VARCHAR(500) NOT NULL,
  `Forename` VARCHAR(45) NULL,
  `Surname` VARCHAR(45) NULL,
  `Year` INT NULL,
  `StaffId` VARCHAR(10) NOT NULL,
  `Degree` VARCHAR(45) NOT NULL,
  `Salt` VARCHAR(250) NULL,
  `Username` VARCHAR(45) NULL,
  PRIMARY KEY (`Matric`),
  INDEX `fk_Student_Advisor1_idx` (`StaffId` ASC),
  INDEX `fk_Student_Degree1_idx` (`Degree` ASC),
  CONSTRAINT `fk_Student_Advisor1`
    FOREIGN KEY (`StaffId`)
    REFERENCES `mydb`.`Advisor` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Student_Degree1`
    FOREIGN KEY (`Degree`)
    REFERENCES `mydb`.`Degree` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `mydb`.`DeptHead`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`DeptHead` (
  `StaffId` VARCHAR(10) NOT NULL,
  `Year` VARCHAR(45) NULL,
  PRIMARY KEY (`StaffId`),
  CONSTRAINT `fk_Dept Head_Staff1`
    FOREIGN KEY (`StaffId`)
    REFERENCES `mydb`.`Staff` (`StaffId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`TeachingCommittee`
-- -----------------------------------------------------
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
CREATE TABLE IF NOT EXISTS `mydb`.`Course` (
  `CourseId` VARCHAR(15) NOT NULL,
  `Name` VARCHAR(45) NULL,
  `Aim` VARCHAR(300) NULL,
  `Credit` VARCHAR(45) NULL,
  `School` VARCHAR(45) NOT NULL,
  `Level` ENUM('1','2','3','4','M') NULL,
  PRIMARY KEY (`CourseId`),
  INDEX `fk_Course_School1_idx` (`School` ASC),
  CONSTRAINT `fk_Course_School1`
    FOREIGN KEY (`School`)
    REFERENCES `mydb`.`School` (`Name`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`StudentHasCourse`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`StudentHasCourse` (
  `StudentHasCourseId` VARCHAR(45) NOT NULL,
  `Grade` ENUM('A1','A2','A3','A4','A5','B1','B2','B3','C1','C2','C3','D1','D2','D3','E1','E2','E3','F1','F2','F3','G1','G2','H','') NULL,
  `Status` ENUM('Completed','','Uncompleted','Failed') NULL,
  `Matric` VARCHAR(8) NOT NULL,
  `CourseId` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`StudentHasCourseId`, `Matric`, `CourseId`),
  INDEX `fk_StudentHasCourse_Student1_idx` (`Matric` ASC),
  INDEX `fk_StudentHasCourse_Course1_idx` (`CourseId` ASC),
  CONSTRAINT `fk_StudentHasCourse_Student1`
    FOREIGN KEY (`Matric`)
    REFERENCES `mydb`.`Student` (`Matric`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_StudentHasCourse_Course1`
    FOREIGN KEY (`CourseId`)
    REFERENCES `mydb`.`Course` (`CourseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `mydb`.`CourseList`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`CourseList` (
  `CourseListId` VARCHAR(45) NOT NULL,
  `School` VARCHAR(45) NOT NULL,
  `Level` INT NULL,
  PRIMARY KEY (`CourseListId`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Groups`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Groups` (
  `GroupId` INT NOT NULL,
  `Credits` VARCHAR(45) NULL,
  `CourseListId` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`GroupId`, `CourseListId`),
  INDEX `fk_Group_CourseList1_idx` (`CourseListId` ASC),
  CONSTRAINT `fk_Group_CourseList1`
    FOREIGN KEY (`CourseListId`)
    REFERENCES `mydb`.`CourseList` (`CourseListId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`DegreeHasCourseList`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`DegreeHasCourseList` (
  `CourseListId` VARCHAR(45) NOT NULL,
  `Degree` VARCHAR(45) NOT NULL,
  `School` VARCHAR(45) NOT NULL,
  `Year` INT NULL,
  PRIMARY KEY (`CourseListId`, `Degree`, `School`),
  INDEX `fk_DegreeHasCourseList_CourseList1_idx` (`CourseListId` ASC),
  INDEX `fk_DegreeHasCourseList_Degree1_idx` (`Degree` ASC, `School` ASC),
  CONSTRAINT `fk_DegreeHasCourseList_CourseList1`
    FOREIGN KEY (`CourseListId`)
    REFERENCES `mydb`.`CourseList` (`CourseListId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_DegreeHasCourseList_Degree1`
    FOREIGN KEY (`Degree` , `School`)
    REFERENCES `mydb`.`Degree` (`Name` , `School`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`GroupHasCourse`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`GroupHasCourse` (
  `GroupId` INT NOT NULL,
  `CourseListId` VARCHAR(45) NOT NULL,
  `CourseId` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`GroupId`, `CourseListId`, `CourseId`),
  INDEX `fk_Course_has_Group_Group1_idx` (`GroupId` ASC, `CourseListId` ASC),
  INDEX `fk_GroupHasCourse_Course1_idx` (`CourseId` ASC),
  CONSTRAINT `fk_Course_has_Group_Group1`
    FOREIGN KEY (`GroupId` , `CourseListId`)
    REFERENCES `mydb`.`Groups` (`GroupId` , `CourseListId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_GroupHasCourse_Course1`
    FOREIGN KEY (`CourseId`)
    REFERENCES `mydb`.`Course` (`CourseId`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
