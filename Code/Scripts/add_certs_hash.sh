#! /bin/sh
OPENSSL=/usr/bin/openssl
CERTDIR=/etc/ssl/certs

opkg update
opkg install ca-certificates

# Install openssl-util if need
[ ! -f ${OPENSSL} ] && opkg update && opkg install openssl-util

for CERTFILE in ${CERTDIR}/*; do
	# create symbolic link from hash
	echo -en "Certificate ${CERTFILE##*/}\n generating hash: "
	HASH=$(${OPENSSL} x509 -hash -noout -in ${CERTFILE})
	echo "$HASH"

	# handle hash collision
	SUFFIX=0
	while [ -h "${CERTDIR}/${HASH}.${SUFFIX}" ]; do
		let "SUFFIX += 1"
	done

	echo "linking ${HASH}.${SUFFIX} -> ${CERTFILE##*/}"
	ln -s ${CERTFILE##*/} ${CERTDIR}/${HASH}.${SUFFIX}
done



