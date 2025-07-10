import logging
import localstack_client.session as boto3
from botocore.exceptions import ClientError
import json
import os

logger = logging.getLogger()
logging.basicConfig(level=logging.INFO, format='%(asctime)s: %(levelname)s: %(message)s')

s3_client = boto3.client("s3") 
s3_resource = boto3.resource("s3")

def list_buckets():
    try:
        response = s3_resource.buckets.all()
    except ClientError:
        logger.exception('Could not list S3 bucket from LocalStack.')
        raise
    else:
        return response


def main():
    logger.info('Listing S3 buckets from LocalStack...')
    s3 = list_buckets()
    logger.info('S3 bucket names: ')
    for bucket in s3:
        logger.info(bucket.name)


if __name__ == '__main__':
    main()


 
