#!/usr/bin/perl -w
#
# $Id:$ olri
#
use strict;
use IO::File;
use File::Copy;

# this script splits datafiles by airplane-id and put the content into
# a separate airplane-id directory, copying logs into
#
if ( ! defined $ENV{"PAPARAZZI_HOME"} ) {
	die "Error PAPARAZZI_HOME isn't  set, ABORT !";
}
my $dirname = "$ENV{"PAPARAZZI_HOME"}/var/logs";

# files aus dirname in @datas einlesen
opendir(DIR, $dirname) || die "can't opendir $dirname: $!";
my @datas = grep { -f "$dirname/$_" && /\.data$/ } readdir(DIR);
closedir DIR;

print join "\n", @datas, "\n";

# oeffne jedes file und verteile inhalte anhand der flugzeugnummern
my $data;
foreach $data (@datas) {
    print $data, ":";
    open LOGFILE, $data or die "open: can't open $data";
    my %h;
    my $nr;
    while (<LOGFILE>) {
	chomp;
	my $line = $_;
	my @a = split '\s', $line;
	$nr = $a[1];
	if ( ! defined $h{$nr} ) {
	    mkdir "$dirname/$nr" unless -d "$dirname/$nr";
	    $h{$nr} = new IO::File;
	    open $h{$nr}, ">$dirname/$nr/$data" or
		die "open: $dirname/$nr/$data $!";
	    print " ", $nr;
	    my $log = $data;
	    $log =~ s/\.data$/.log/o;
	    copy ( "$dirname/$log", "$dirname/$nr/$log" ) or die "copy failed: $log $!";

	}
	print {$h{$nr}} ("$line\n");
    }
    print "\n";
    # close all subfiles
    foreach $nr (keys %h) {
	close $h{$nr} or die "close: $nr $!";
	print "closing: $dirname/$nr/$data\n";
    }
    close LOGFILE or die "close: can't close $data";
}
exit 0;
