import logging
import localstack_client.session as boto3
import botocore
import json
import os

logger = logging.getLogger()
logging.basicConfig(level=logging.INFO, format='%(asctime)s: %(levelname)s: %(message)s')

s3_client = boto3.client("s3")

def create_bucket(bucket_name):
    try:
        response = s3_client.create_bucket(Bucket=bucket_name)
    except botocore.ClientError:
        logger.exception('Could not create S3 bucket locally.')
        raise
    else:
        return response

def main():
    bucket = 'testwebsite'
    logger.info('Creating bucket...')
    response = create_bucket(bucket)
    logger.info('Bucket created successfully.')

if __name__ == '__main__':
    main()