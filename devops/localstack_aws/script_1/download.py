import logging
import localstack_client.session as boto3
from botocore.exceptions import ClientError
import botocore
import json
import os

logger = logging.getLogger()
logging.basicConfig(level=logging.INFO, format='%(asctime)s: %(levelname)s: %(message)s')

s3_resource = boto3.resource('s3')

def download_file(file_name, bucket, object_name):
    try:
        response = s3_resource.Bucket(bucket).download_file(object_name, file_name)
    except ClientError:
        logger.exception('Could not download file to S3 bucket.')
        raise
    else:
        return response


def main():
    file_name = 'D:\Desktop\\tho_lab4\index.html'
    object_name = 'index.html'
    bucket = 'testwebsite'

    logger.info('Downloading file...')
    s3 = download_file(file_name, bucket, object_name)
    logger.info('File downloaded from S3 bucket successfully.')


if __name__ == '__main__':
    main()

