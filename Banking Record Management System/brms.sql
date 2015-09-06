-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Sep 06, 2015 at 09:43 PM
-- Server version: 5.5.44-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `brms`
--

-- --------------------------------------------------------

--
-- Table structure for table `account_trans`
--

CREATE TABLE IF NOT EXISTS `account_trans` (
  `id` varchar(20) NOT NULL DEFAULT '',
  `balance` int(20) DEFAULT NULL,
  `last_changes` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `account_trans`
--

INSERT INTO `account_trans` (`id`, `balance`, `last_changes`) VALUES
('147255 ', 5000, '2015-05-20 20:03:07'),
('147256 ', 60000, '2015-05-20 20:01:33'),
('147257 ', 30000, '2015-05-20 19:59:50'),
('147258 ', 98000, '2015-05-19 23:43:22'),
('147259 ', 20000, '2015-05-20 19:58:25');

-- --------------------------------------------------------

--
-- Table structure for table `client_info`
--

CREATE TABLE IF NOT EXISTS `client_info` (
  `id` varchar(20) NOT NULL DEFAULT '',
  `name` varchar(20) DEFAULT NULL,
  `addr` varchar(50) DEFAULT NULL,
  `dob` varchar(20) DEFAULT NULL,
  `phno` varchar(20) DEFAULT NULL,
  `dateAdded` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `client_info`
--

INSERT INTO `client_info` (`id`, `name`, `addr`, `dob`, `phno`, `dateAdded`) VALUES
('147255 ', 'Rohit Agarwal ', 'BITS, Pilani. ', '5-9-92 ', '789-548-8754 ', '2015-05-20 20:03:07'),
('147256 ', 'Shweta Jha ', '4, M.G Road, Mumbai ', '25-7-90 ', '56-897-7848 ', '2015-05-20 20:01:33'),
('147257 ', 'Mark Peterson ', '34 M.Road, Kolkata ', '17-5-87 ', '78-458-978 ', '2015-05-20 19:59:50'),
('147258 ', 'Himanshu Mishra ', 'Kings Road,Howrah ', '2-3-90 ', '987456132 ', '2015-05-19 23:43:22'),
('147259 ', 'John Watson ', '9 Ave, New Delhi ', '2-8-81 ', '87-489-975 ', '2015-05-20 19:58:25');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
